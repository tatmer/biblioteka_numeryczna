#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept> // Do obsługi std::exception
#include "approximation.h" // Używamy naszej biblioteki

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

    // --- Poprawny test ---
    std::cout << "\n--- Correct Test: Valid Degree Approximation ---" << std::endl;
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
        for (double x_val = a; x_val <= b; x_val += 0.5) { // Zmiana nazwy zmiennej, aby uniknąć konfliktu z 'x' z pętli for
            double exact_val = my_function(x_val);
            double approx_val = evaluate_polynomial(coeffs, x_val);
            std::cout << x_val << "\t\t" << exact_val << "\t\t" << approx_val << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Caught unexpected error in correct test: " << e.what() << std::endl;
    }

    // --- Błędny test: Ujemny stopień wielomianu ---
    std::cout << "\n--- Error Test: Negative Polynomial Degree ---" << std::endl;
    int invalid_degree = -1; // Nieprawidłowy stopień
    std::cout << "Attempting to approximate with degree = " << invalid_degree << std::endl;

    try {
        polynomial_approximation(my_function, invalid_degree, a, b);
        std::cerr << "Error: Expected an exception for negative degree, but none was thrown." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught expected error: " << e.what() << std::endl;
    }

    return 0;
}