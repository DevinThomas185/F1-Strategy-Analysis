#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <map>
#include "enums.hpp"

struct LinearRegressionResult {
    double gradient;
    double y_intercept;
};

LinearRegressionResult calculateLinearRegression(const std::vector<double>& x_values, const std::vector<double>& y_values);

double standard_deviation(const std::vector<double>& values);

#endif // ANALYSIS_HPP
