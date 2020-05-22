#include <iostream>
#include "lab03svg.h"
#include <windows.h>
#include <stdio.h>
#include <sstream>

DWORD WINAPI GetVersion(void);

string
make_info_text1()
{
    stringstream buffer;

    DWORD dwVersion = 0;
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
        buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")  "<<'\n';
        //printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);
    }
    return buffer.str();
}

string
make_info_text2()
{
    stringstream buffer;

    char system_dir[MAX_PATH];
    char computer_name[MAX_COMPUTERNAME_LENGTH+1];
    DWORD size = sizeof(computer_name);
    GetSystemDirectory(system_dir, MAX_PATH);
    GetComputerNameA(computer_name, &size);
    buffer << "Computer Name:" <<  computer_name;

    return buffer.str();
}

vector<string> colors(size_t bin_count)
{
    vector<string> cin_colors(bin_count);
    for (size_t i = 0; i < bin_count; i++)
    {
        getline(cin, cin_colors[i]);
    }
    return cin_colors;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";

}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";

}

void svg_rect(double x, double y, double width, double height,string stroke,string fill)
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    size_t bin_count = bins.size();
    vector<string> colors_vec(bin_count);
    colors_vec=colors(bin_count);
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    size_t t=0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,colors_vec[t],colors_vec[t]);
        top += BIN_HEIGHT;
        t++;
    }
    svg_text(1,top+ 3*TEXT_BASELINE, make_info_text1());
    svg_text(1,top+ 4*TEXT_BASELINE, make_info_text2());
    svg_end();
}

/*string make_info_text()
{
    stringstream buffer;
    // TODO: получить версию системы, записать в буфер.
    // TODO: получить имя компьютера, записать в буфер.
    return buffer.str();
}*/
