#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "interpolation.h" // Używamy naszej biblioteki

// Pomocnicza funkcja do drukowania punktów
void print_nodes(const std::vector<Point>& nodes) {
    std::cout << "Using nodes: ";
    for (const auto& node : nodes) {
        std::cout << "(" << node.first << ", " << node.second << ") ";
    }
    std::cout << std::endl;
}

// Przykładowa funkcja, którą będziemy interpolować: f(x) = sin(x)
double original_function(double x) {
    return sin(x);
}

int main() {
    std::cout << "--- Example: Lagrange and Newton Interpolation ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    // --- Poprawny test: Interpolacja sin(x) ---
    std::cout << "\n--- Correct Test: Interpolating sin(x) ---" << std::endl;

    // Generujemy węzły interpolacji na podstawie funkcji sin(x)
    std::vector<Point> interpolation_nodes;
    for (int i = 0; i <= 4; ++i) {
        double x_node = i * 1.0; // Węzły: 0, 1, 2, 3, 4
        interpolation_nodes.push_back({ x_node, original_function(x_node) });
    }

    print_nodes(interpolation_nodes);

    // Punkt, w którym chcemy znaleźć wartość interpolowaną
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

    // Sprawdzenie, czy obie metody dają ten sam wynik (powinny!)
    // Weryfikacja tylko jeśli nie było błędów w poprzednich krokach
    try {
        double lagrange_res = lagrange_interpolation(interpolation_nodes, x_to_interpolate);
        double newton_res = newton_interpolation(interpolation_nodes, x_to_interpolate);
        std::cout << "\nVerification: Difference between methods = " << std::abs(lagrange_res - newton_res) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Verification skipped due to previous errors: " << e.what() << std::endl;
    }


    // --- Błędny test: Pusta lista węzłów ---
    std::cout << "\n--- Error Test: Empty nodes list ---" << std::endl;
    std::vector<Point> empty_nodes;
    try {
        std::cout << "Attempting Lagrange interpolation with empty nodes..." << std::endl;
        lagrange_interpolation(empty_nodes, 1.0);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for Lagrange: " << e.what() << std::endl;
    }

    try {
        std::cout << "Attempting Newton interpolation with empty nodes..." << std::endl;
        newton_interpolation(empty_nodes, 1.0);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for Newton: " << e.what() << std::endl;
    }

    // --- Błędny test: Duplikat wartości X w węzłach ---
    std::cout << "\n--- Error Test: Duplicate X values in nodes ---" << std::endl;
    std::vector<Point> duplicate_x_nodes = {{0.0, 0.0}, {1.0, 1.0}, {1.0, 2.0}, {2.0, 4.0}};
    print_nodes(duplicate_x_nodes); // Pokaż, które węzły są błędne
    try {
        std::cout << "Attempting Lagrange interpolation with duplicate X values..." << std::endl;
        lagrange_interpolation(duplicate_x_nodes, 0.5);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for Lagrange: " << e.what() << std::endl;
    }

    try {
        std::cout << "Attempting Newton interpolation with duplicate X values..." << std::endl;
        newton_interpolation(duplicate_x_nodes, 0.5);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught expected error for Newton: " << e.what() << std::endl;
    }

    return 0;
}