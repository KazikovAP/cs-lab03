#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "histogram.h"
#include "lab03svg.h"

using namespace std;

vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
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

int main(int argc,char*argv[])
{
    int printf(const char* format, ...);
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    // Commander Shepard was born in 2154.
    return 0;

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
}
