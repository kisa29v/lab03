#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>


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
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size=item_size*item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
   buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input
download(const string& address, bool verbose) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
        {
            CURLcode res;
            if (verbose){
                curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            }
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            if (res)
            {
                cerr << curl_easy_strerror(res) << endl;
                exit(1);
            }
        }
    curl_easy_cleanup(curl);
    return read_input(buffer, false);
        }
Verb input_with_verb(int argc, char* argv[])
{
    Verb use;

    use.verbose=false;
    use.help=false;
    use.urladress=0;

    for (int i=1; i<argc; i++)
    {
        if (argv[i][0]=='-')
        {
            if (strcmp(argv[i], "-verbose") == 0)
            {
                use.verbose=true;
            }
            else
            {
                use.help=true;
            }
        }
        else
        {
            use.urladress=argv[i];
        }
    }

    return use;
}
int main(int argc, char* argv[])
{   Input input;
    auto data=input_with_verb(argc,argv);
        if (data.help)
    {
        cerr <<"For using CURLOPT_VERBOSE mode enter ''-verbose''" << "\n";
        exit(2);
    }
    if (data.urladress)
    {
        input=download(data.urladress,data.verbose);
    }
    else
    {
        input=read_input(cin, true);

    const auto bins = make_histogram(input);

    show_histogram_svg(bins);
    return 0;
}
}


