#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "lab03svg.h"

using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
};

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

    if(prompt==1)
    {
        cerr << "Enter number count:";
    }
    size_t number_count;
    cin >> number_count;

    if(prompt==1)
    {
        cerr <<"Enter numbers:";
    }
    data.numbers = input_numbers(in, number_count);

    size_t bin_count;
    if(prompt==1)
    {
        cerr <<"Enter bin count:";
    }
    cin >> bin_count;
    data.bin_count = bin_count;
    return data;
}


vector<size_t> make_histogram (struct Input Input)
{
    double min = 0;
    double max = 0;
    find_minmax(Input, min, max);
    vector<size_t> bins(Input.bin_count);
    for (double number : Input.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * Input.bin_count);
        if (bin == Input.bin_count)
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

int
main()
{
    const auto input = read_input(cin, true);

    const auto bins = make_histogram(input);

    show_histogram_svg(bins);

    return 0;
}
