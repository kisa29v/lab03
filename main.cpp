#include <iostream>
#include <vector>
#include "histogram.h"
#include <curl/curl.h>

using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
struct Input
{
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
read_input(istream& in, bool prompt)
{
    Input data;
    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;
    if (prompt == true)
    {
        cerr << "Enter numbers: ";
    }

    data.numbers = input_numbers(in, number_count);

    if (prompt == true)
    {
        cerr << "Enter column count: ";
    }
    cin >> data.bin_count;

    return data;
}
vector<size_t> make_histogram(Input data)
{
    double min = data.numbers[0];
    double max = data.numbers[0];
    find_minmax(data.numbers, min, max);
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
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;

    }
    curl_global_init(CURL_GLOBAL_ALL);
    //auto in = read_input(cin, true);

    // Ввод чисел заменен вызовом функции:
    //const auto numbers = input_numbers(cin, number_count);

    // Обработка данных

    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);

    show_histogram_svg(bins);

    // Вывод данных
    /*const size_t SCREEN_WIDTH = 80;
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
    }*/
    /*svg_begin(width, height);
    svg_end();
    svg_text(left, baseline, text);
    svg_rect(x, y, width, height, stroke, fill);
    show_histogram_svg(bins);*/


    return 0;
}


