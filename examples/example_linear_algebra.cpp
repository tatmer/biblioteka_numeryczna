#include <iostream>
#include <vector>
#include <iomanip>
#include "linear_algebra.h" // U¿ywamy naszej biblioteki

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

    // Definicja przyk³adowego uk³adu równañ
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

    // Drugi przyk³ad z macierz¹ osobliw¹
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

    return 0;
}