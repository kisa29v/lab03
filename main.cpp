#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <windows.h>

using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
int main()
{   /*
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    // ���� ����� ������� ������� �������:
    const auto numbers = input_numbers(cin, number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min,max;
    find_minmax(numbers,min,max);
    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_svg(bins);*/
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD mask_2 = 0x0000ff;
   if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_2;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        printf("Windows v%u.%u (build %u)", version_major, version_minor, build);
    }
    return 0;
}


