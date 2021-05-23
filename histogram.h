#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};
void
find_minmax(const vector<double>& numbers, double& min, double& max);
vector<size_t> make_histogram(Input data);
#endif // HISTOGRAM_H_INCLUDED
