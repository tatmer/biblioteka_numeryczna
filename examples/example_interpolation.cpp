#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "interpolation.h" // U¿ywamy naszej biblioteki

// Pomocnicza funkcja do drukowania punktów
void print_nodes(const std::vector<Point>& nodes) {
    std::cout << "Using nodes: ";
    for (const auto& node : nodes) {
        std::cout << "(" << node.first << ", " << node.second << ") ";
    }
    std::cout << std::endl;
}

// Przyk³adowa funkcja, któr¹ bêdziemy interpolowaæ: f(x) = sin(x)
double original_function(double x) {
    return sin(x);
}

int main() {
    std::cout << "--- Example: Lagrange and Newton Interpolation ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    // Generujemy wêz³y interpolacji na podstawie funkcji sin(x)
    std::vector<Point> interpolation_nodes;
    for (int i = 0; i <= 4; ++i) {
        double x = i * 1.0; // Wêz³y: 0, 1, 2, 3, 4
        interpolation_nodes.push_back({ x, original_function(x) });
    }

    print_nodes(interpolation_nodes);

    // Punkt, w którym chcemy znaleŸæ wartoœæ interpolowan¹
    double x_to_interpolate = 2.5;
    double exact_value = original_function(x_to_interpolate);

    std::cout << "\nInterpolating at x = " << x_to_interpolate << std::endl;
    std::cout << "Exact value f(" << x_to_interpolate << ") = sin(" << x_to_interpolate << ") = " << exact_value << std::endl;

    // --- Interpolacja Lagrange'a ---
    std::cout << "\n--- Lagrange Interpolation ---" << std::endl;
    try {
        double result_lagrange = lagrange_interpolation(interpolation_nodes, x_to_interpolate);
        std::cout << "Result: " << result_lagrange << std::endl;
        std::cout << "Error:  " << std::abs(result_lagrange - exact_value) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // --- Interpolacja Newtona ---
    std::cout << "\n--- Newton Interpolation ---" << std::endl;
    try {
        double result_newton = newton_interpolation(interpolation_nodes, x_to_interpolate);
        std::cout << "Result: " << result_newton << std::endl;
        std::cout << "Error:  " << std::abs(result_newton - exact_value) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Sprawdzenie, czy obie metody daj¹ ten sam wynik (powinny!)
    double lagrange_res = lagrange_interpolation(interpolation_nodes, x_to_interpolate);
    double newton_res = newton_interpolation(interpolation_nodes, x_to_interpolate);
    std::cout << "\nVerification: Difference between methods = " << std::abs(lagrange_res - newton_res) << std::endl;

    return 0;
}