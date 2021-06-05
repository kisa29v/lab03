#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>


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
Input
read_input(istream& in, bool promt) {
    Input data;
    if(promt){
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    data.numbers = input_numbers(in, number_count);
    if (promt){
        cerr <<"Enter bin count:";
    }
    in >> data.bin_count;

    return data;
}
int main(int argc, char* argv[])
{   curl_global_init(CURL_GLOBAL_ALL);
    if (argc > 1){
        CURL *curl = curl_easy_init();
        if(curl){
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
                }
                  }
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin, true);

    const auto bins = make_histogram(input);

    show_histogram_svg(bins);
    return 0;
}


