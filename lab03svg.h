#ifndef LAB03SVG_H_INCLUDED
#define LAB03SVG_H_INCLUDED

#include <vector>
#include <string>
#include <windows.h>
#include <stdio.h>

using namespace std;

DWORD WINAPI GetVersion(void);


string make_info_text1();
string make_info_text2();


vector<string> colors(size_t bin_count);

void svg_begin(double width, double height);

void svg_end();

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height,string stroke,string fill = "black");

void show_histogram_svg(const vector<size_t>& bins, Input& data);


#endif // LAB03SVG_H_INCLUDED
