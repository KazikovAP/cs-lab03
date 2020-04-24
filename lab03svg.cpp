#include <iostream>
#include "lab03svg.h"

vector<string> colors(size_t bin_count)
{
    vector<string> cin_colors(bin_count);
    for (size_t i = 0; i < bin_count; i++)
    {
        getline(cin, cin_colors[i]);
    }
    return cin_colors;
}
