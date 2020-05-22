#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "histogram.h"
#include "lab03svg.h"
#include <windows.h>
#include <stdio.h>



using namespace std;

vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;
    if (prompt)
    {
        cerr << "Enter number count:";
        in >> number_count;

        cerr << "Enter numbers:";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter column count:";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }
    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address)
{
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());

        /* Perform the request */
        res = curl_easy_perform(curl);

        if(!res)
        {
            /* check the size */
            double dl;
            res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &dl);
            if(!res)
            {
                //printf("Downloaded %.0f bytes\n", dl);
                //cerr<<dl;
                cerr << "Downloaded:"<<dl<<"bytes\n";
            }
        }
    }

    return read_input(buffer, false);
}

//DWORD WINAPI GetVersion(void);
//int printf(const char* format, ...);

int main(int argc,char*argv[])
{
    /*int printf(const char* format, ...);
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    // Commander Shepard was born in 2154.*/

    Input input;
    if(argc>1)
    {
        input = download(argv[1]);
    }
    else
    {
        input=read_input(cin,true);
    }


    const auto bins = make_histogram(input);

    show_histogram_svg(bins);

    /*DWORD dwVersion = 0;
    dwVersion = GetVersion();
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0x000000ff;

    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    printf("Windows 16x-version is %x\n", version );
    printf("Windows decimal-version is %u\n", version );
    printf("Platform is %u\n", platform );
    printf("Windows major version is %u\n", version_major );
    printf("Windows minor version is %u\n", version_minor );

    if ((info & 0x40000000) == 0)
    {
        DWORD build = platform;
        printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);
    }

    char system_dir[MAX_PATH];
    char computer_name[MAX_COMPUTERNAME_LENGTH+1];
    DWORD size = sizeof(computer_name);
    GetSystemDirectory(system_dir, MAX_PATH);
    GetComputerNameA(computer_name, &size);
    printf("System directory: %s\n", system_dir); // System directory: C:\Windows
    printf("Computer name: %s\n", computer_name);
*/



    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min, max;

    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_count);
return 0;
}
