#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits> // Required for std::numeric_limits
#include <stdexcept> // Required for std::invalid_argument (if using exceptions)
#include "integration.h" // Use our library

// Test function
double f1(double x) {
    return x * x * pow(sin(x), 3);
}

int main() {
    double a = 1.0, b = 4.764798248;
    double exact_f1 = -10.1010101105917;

    std::cout << "--- Example: Numerical Integration ---" << std::endl;
    std::cout << std::fixed << std::setprecision(10);

    int intervals = 1000;
    
    // --- Correctness Tests ---
    std::cout << "\n--- Correctness Tests ---" << std::endl;

    double result_rect = rectangle_rule(f1, a, b, intervals);
    std::cout << "Rectangle Rule: " << result_rect << ", Error: " << std::abs(exact_f1 - result_rect) << std::endl;

    double result_trap = trapezoid_rule(f1, a, b, intervals);
    std::cout << "Trapezoid Rule: " << result_trap << ", Error: " << std::abs(exact_f1 - result_trap) << std::endl;

    double result_simp = simpson_rule(f1, a, b, intervals);
    std::cout << "Simpson's Rule: " << result_simp << ", Error: " << std::abs(exact_f1 - result_simp) << std::endl;

    int gl_nodes = 4;
    int gl_subintervals = 100;
    double result_gl = gauss_legendre_quadrature(f1, a, b, gl_nodes, gl_subintervals);
    std::cout << "Gauss-Legendre (" << gl_nodes << " nodes, " << gl_subintervals << " sub): " << result_gl 
              << ", Error: " << std::abs(exact_f1 - result_gl) << std::endl;

    // --- Erroneous Test Case ---
    std::cout << "\n--- Erroneous Test: Invalid Input ---" << std::endl;
    int invalid_intervals_zero = 0; // Number of intervals cannot be zero

    std::cout << "Attempting Rectangle Rule with 0 intervals: ";
    try {
        double result_rect_err = rectangle_rule(f1, a, b, invalid_intervals_zero);
        if (std::isnan(result_rect_err)) {
            std::cout << "Result is NaN (as expected for error)." << std::endl;
        } else {
            std::cout << "Unexpected result: " << result_rect_err << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught unexpected exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Another erroneous test: Simpson's rule with an odd number of intervals
    int invalid_simp_intervals_odd = 999;
    std::cout << "Attempting Simpson's Rule with 999 (odd) intervals: ";
    try {
        double result_simp_err = simpson_rule(f1, a, b, invalid_simp_intervals_odd);
        if (std::isnan(result_simp_err)) {
            std::cout << "Result is NaN (as expected for error)." << std::endl;
        } else {
            std::cout << "Unexpected result: " << result_simp_err << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught unexpected exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}