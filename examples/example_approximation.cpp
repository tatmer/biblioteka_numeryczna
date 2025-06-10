#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "approximation.h" // Use our library

// The function to be approximated
double my_function(double x) {
    return exp(x) * cos(5 * x) - pow(x, 3);
}

// Helper to evaluate a polynomial given its coefficients
double evaluate_polynomial(const std::vector<double>& coeffs, double x) {
    double result = 0.0;
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * pow(x, i);
    }
    return result;
}

int main() {
    std::cout << "--- Example: Polynomial Approximation ---" << std::endl;

    double a = -1.0, b = 2.0;
    int degree = 4;

    std::cout << "Approximating f(x) = exp(x)*cos(5*x) - x^3 on [" << a << ", " << b << "] with a polynomial of degree " << degree << std::endl;

    try {
        std::vector<double> coeffs = polynomial_approximation(my_function, degree, a, b);

        std::cout << "\nCalculated coefficients [a0, a1, ...]:" << std::endl;
        for (size_t i = 0; i < coeffs.size(); ++i) {
            std::cout << "a" << i << " = " << std::scientific << coeffs[i] << std::endl;
        }

        // Print a table of values
        std::cout << "\n--- Comparison Table ---" << std::endl;
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "x\t\tExact f(x)\tApprox P(x)" << std::endl;
        for (double x = a; x <= b; x += 0.5) {
            double exact_val = my_function(x);
            double approx_val = evaluate_polynomial(coeffs, x);
            std::cout << x << "\t\t" << exact_val << "\t\t" << approx_val << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}