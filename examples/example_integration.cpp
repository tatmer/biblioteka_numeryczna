#include <iostream>
#include <cmath>
#include <iomanip>
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

    return 0;
}