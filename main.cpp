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

    // Ввод чисел заменен вызовом функции:
    const auto numbers = input_numbers(cin, number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    double min,max;
    find_minmax(numbers,min,max);
    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_svg(bins);*/
    DWORD WINAPI GetVersion(void);
    printf("Windows (decimal) version is %u.\n", GetVersion());
    printf("WINDOWS (16x) version is %x. \n",GetVersion());
    return 0;
}


