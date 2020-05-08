#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
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

vector<size_t> make_histogram (Input data)
{
    double min = 0;
    double max = 0;
    find_minmax(data, min, max);
    vector<size_t> bins(data.bin_count);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;

    if(prompt==true)
        cerr << "Enter number count:";
    size_t number_count;
    cin >> number_count;

    if(prompt==true)
        cerr <<"Enter numbers:";
    data.numbers = input_numbers(in, number_count);

    size_t bin_count;
    if(prompt==true)
        cerr <<"Enter bin count:";
    cin >> data.bin_count;

    return data;
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

int main(int argc,char*argv[])
{
    if(argc>1)
    {
        CURL* curl =curl_easy_init();
        size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
        {
            stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
            const char* char_items = reinterpret_cast<const char*>(items);
            size_t data_size;
            data_size=item_size* item_count;
            buffer->write(char_items, data_size);
            return data_size;
        }
    }



{
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);

    const auto bins = make_histogram(input);

    show_histogram_svg(bins);

    return 0;
}
}
