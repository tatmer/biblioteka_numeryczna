#include "approximation.h"
#include "integration.h" // Using our own integration module!
#include <stdexcept>
#include <cmath>

std::vector<double> polynomial_approximation(std::function<double(double)> func, int degree, double a, double b) {
    if (degree < 0) {
        throw std::invalid_argument("Degree of polynomial must be non-negative.");
    }

    int n = degree + 1;
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> B(n);

    // Build the matrix A (Gram matrix) and vector B
    // Integrals are computed using Simpson's rule from our library
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto integrand = [i, j](double x) { return std::pow(x, i + j); };
            A[i][j] = simpson_rule(integrand, a, b, 1000);
        }
        auto integrand_b = [func, i](double x) { return func(x) * std::pow(x, i); };
        B[i] = simpson_rule(integrand_b, a, b, 1000);
    }

    // Solve the linear system Ax = B using Gaussian elimination
    // This part should ideally be in a separate linear_algebra module
    for (int i = 0; i < n; ++i) {
        // Find pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(A[j][i]) > std::abs(A[pivot][i])) {
                pivot = j;
            }
        }
        std::swap(A[i], A[pivot]);
        std::swap(B[i], B[pivot]);

        // Check for singularity
        if (std::abs(A[i][i]) < 1e-12) {
            throw std::runtime_error("Matrix is singular or nearly singular; cannot solve the system.");
        }

        // Normalize row
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            B[k] -= factor * B[i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    // Back substitution
    std::vector<double> coeffs(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += A[i][j] * coeffs[j];
        }
        coeffs[i] = (B[i] - sum) / A[i][i];
    }

    return coeffs;
}