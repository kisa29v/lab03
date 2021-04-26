#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
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
Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    return data;
}
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min = numbers[0];
    double max = numbers[0];
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}
int main()
{   size_t number_count;
    size_t bin_count;
    read_input(cin);

    // Ввод чисел заменен вызовом функции:
    const auto numbers = input_numbers(cin, number_count);

    // Обработка данных

    const auto bins = make_histogram(numbers, bin_count);

    // Вывод данных
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;

    show_histogram_svg(bins);
    size_t height;
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
    /*svg_begin(width, height);
    svg_end();
    svg_text(left, baseline, text);
    svg_rect(x, y, width, height, stroke, fill);
    show_histogram_svg(bins);*/


    return 0;
}


