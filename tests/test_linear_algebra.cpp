#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept> // For std::runtime_error or std::invalid_argument
#include "linear_algebra.h" // Używamy naszej biblioteki

// Pomocnicza funkcja do drukowania wektora
void print_vector(const Vector& vec, const std::string& name) {
    std::cout << "Vector " << name << ": [ ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "--- Example: Solving Linear Equations Ax = b ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);

    // Definicja przykładowego układu równań
    Matrix A = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 10}
    };
    Vector b = { 1, 1, 1 };

    std::cout << "\nSolving system with Gauss Elimination:" << std::endl;
    try {
        Vector x_gauss = solve_gauss(A, b);
        print_vector(x_gauss, "x_gauss");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nSolving system with LU Decomposition:" << std::endl;
    try {
        Vector x_lu = solve_lu(A, b);
        print_vector(x_lu, "x_lu");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Drugi przykład z macierzą osobliwą
    std::cout << "\n--- Example with a singular matrix ---" << std::endl;
    Matrix A_singular = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    Vector b_singular = { 1, 2, 3 };

    std::cout << "\nAttempting to solve with Gauss Elimination:" << std::endl;
    try {
        Vector x_gauss_s = solve_gauss(A_singular, b_singular);
        print_vector(x_gauss_s, "x_gauss_s");
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error: " << e.what() << std::endl;
    }

    // --- Erroneous Test Case ---
    std::cout << "\n--- Erroneous Test: Mismatched Dimensions ---" << std::endl;
    Matrix A_non_square = {
        {1, 2},
        {3, 4},
        {5, 6}
    }; // 3x2 matrix
    Vector b_mismatched = { 1, 2, 3 }; // Size 3

    std::cout << "\nAttempting to solve system with non-square matrix A (3x2) and vector b (size 3):" << std::endl;
    try {
        Vector x_err_gauss = solve_gauss(A_non_square, b_mismatched);
        print_vector(x_err_gauss, "x_err_gauss"); // This line should ideally not be reached
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for Gauss Elimination: " << e.what() << std::endl;
    }

    // Another erroneous test: square matrix, but b has wrong dimension
    Matrix A_square = {
        {1, 2},
        {3, 4}
    }; // 2x2 matrix
    Vector b_wrong_dim = { 1, 2, 3 }; // Size 3

    std::cout << "\nAttempting to solve system with square matrix A (2x2) and vector b (size 3):" << std::endl;
    try {
        Vector x_err_lu = solve_lu(A_square, b_wrong_dim);
        print_vector(x_err_lu, "x_err_lu"); // This line should ideally not be reached
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for LU Decomposition: " << e.what() << std::endl;
    }

    return 0;
}