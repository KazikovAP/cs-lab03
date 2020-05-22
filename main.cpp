#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "lab03svg.h"
#include <windows.h>
#include <stdio.h>



using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector <size_t> make_histogram(const vector<double> &numbers,size_t bin_count)
{
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    for (double number : numbers)
    {
        size_t bin;
        bin = (number - min) / (max - min) * bin_count;
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void show_histogram_text(const vector<size_t> &bins)
{

    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}

DWORD WINAPI GetVersion(void);
int printf(const char* format, ...);

int main()
{
    DWORD dwVersion = 0;
    dwVersion = GetVersion();
    DWORD info = GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    printf("Windows 16x-version is %x\n", version );
    printf("Windows decimal-version is %u\n", version );



    return 0;

    /*int printf(const char* format, ...);
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    printf("n = %08x\n", 0x1234567);

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
    show_histogram_svg(bins, bin_count);*/

}
