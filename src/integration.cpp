#include "integration.h"
#include <stdexcept>
#include <cmath>

// Implementacje są w większości przeniesione z Twojego kodu.

double rectangle_rule(std::function<double(double)> func, double a, double b, int intervals) {
    if (intervals <= 0) throw std::invalid_argument("Number of intervals must be positive.");
    double h = (b - a) / intervals;
    double sum = 0.0;
    for (int i = 0; i < intervals; ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    return sum * h;
}

double trapezoid_rule(std::function<double(double)> func, double a, double b, int intervals) {
    if (intervals <= 0) throw std::invalid_argument("Number of intervals must be positive.");
    double h = (b - a) / intervals;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < intervals; ++i) {
        double x = a + i * h;
        sum += func(x);
    }
    return sum * h;
}

double simpson_rule(std::function<double(double)> func, double a, double b, int intervals) {
    if (intervals <= 0) throw std::invalid_argument("Number of intervals must be positive.");
    if (intervals % 2 != 0) ++intervals; // Simpson's rule requires an even number of intervals
    double h = (b - a) / intervals;
    double sum = func(a) + func(b);
    for (int i = 1; i < intervals; ++i) {
        double x = a + i * h;
        sum += (i % 2 == 0 ? 2.0 : 4.0) * func(x);
    }
    return (h / 3.0) * sum;
}


// --- Gauss-Legendre Quadrature Implementation ---
// Helper struct and function, not exposed in the header
namespace {
    struct GaussNodes {
        std::vector<double> nodes;
        std::vector<double> weights;
    };

    GaussNodes get_gauss_legendre_nodes(int n) {
        GaussNodes data;
        if (n == 2) {
            data.nodes = { -1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };
            data.weights = { 1.0, 1.0 };
        } else if (n == 3) {
            data.nodes = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            data.weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
        } else if (n == 4) {
            data.nodes = {
                -sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0),
                -sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0),
                sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0),
                sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0)
            };
            data.weights = {
                (18.0 - sqrt(30.0)) / 36.0,
                (18.0 + sqrt(30.0)) / 36.0,
                (18.0 + sqrt(30.0)) / 36.0,
                (18.0 - sqrt(30.0)) / 36.0
            };
        } else {
            throw std::invalid_argument("Gauss-Legendre quadrature is only supported for 2, 3, or 4 nodes.");
        }
        return data;
    }
} // anonymous namespace

double gauss_legendre_quadrature(std::function<double(double)> func, double a, double b, int nodes, int subintervals) {
    if (subintervals <= 0) throw std::invalid_argument("Number of subintervals must be positive.");
    
    GaussNodes gn = get_gauss_legendre_nodes(nodes);
    double h = (b - a) / subintervals;
    double result = 0.0;

    for (int j = 0; j < subintervals; ++j) {
        double interval_a = a + j * h;
        double interval_b = interval_a + h;
        double sum = 0.0;

        for (int i = 0; i < nodes; ++i) {
            double t_i = gn.nodes[i];
            double w_i = gn.weights[i];
            double x_i = ((interval_b - interval_a) / 2.0) * t_i + ((interval_a + interval_b) / 2.0);
            sum += w_i * func(x_i);
        }
        result += ((interval_b - interval_a) / 2.0) * sum;
    }

    return result;
}