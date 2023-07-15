#include "analysis.hpp"

LinearRegressionResult calculateLinearRegression(const std::vector<double>& x_values, const std::vector<double>& y_values) {
    size_t n = x_values.size();

    // Calculate the mean of x and y values
    double x_mean = std::accumulate(x_values.begin(), x_values.end(), 0.0) / n;
    double y_mean = std::accumulate(y_values.begin(), y_values.end(), 0.0) / n;

    // Calculate the sum of (x - x_mean) * (y - y_mean) and (x - x_mean)^2
    double numerator = 0.0;
    double denominator = 0.0;

    for (size_t i = 0; i < n; ++i) {
        numerator += (x_values[i] - x_mean) * (y_values[i] - y_mean);
        denominator += std::pow(x_values[i] - x_mean, 2);
    }

    double gradient = numerator / denominator;
    double y_intercept = y_mean - gradient * x_mean;

    return { gradient, y_intercept };
}

double standard_deviation(const std::vector<double>& values) {
    double res = 0;
    double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    for (auto v : values) {
        res += std::pow((v - mean), 2);
    }

    res /= (values.size() - 1); // /(N - 1) Assume a sample of the lap times instead of population
    return std::sqrt(res);
}
