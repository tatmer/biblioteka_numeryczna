#include "interpolation.h"
#include <stdexcept>
#include <vector>

// --- Implementacja interpolacji Lagrange'a ---

double lagrange_interpolation(const std::vector<Point>& nodes, double x) {
    if (nodes.empty()) {
        throw std::invalid_argument("Node vector cannot be empty.");
    }

    double result = 0.0;
    int n = nodes.size();

    for (int i = 0; i < n; ++i) {
        double basis_polynomial = 1.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                // Sprawdzenie, czy wêz³y nie s¹ takie same
                if (nodes[i].first == nodes[j].first) {
                    throw std::invalid_argument("Interpolation nodes must have unique x values.");
                }
                basis_polynomial *= (x - nodes[j].first) / (nodes[i].first - nodes[j].first);
            }
        }
        result += basis_polynomial * nodes[i].second;
    }
    return result;
}


// --- Implementacja interpolacji Newtona ---

namespace { // Ukrywamy funkcje pomocnicze przed u¿ytkownikiem

    // Funkcja obliczaj¹ca ilorazy ró¿nicowe (wspó³czynniki wielomianu Newtona)
    std::vector<double> calculate_divided_differences(const std::vector<Point>& nodes) {
        int n = nodes.size();
        std::vector<double> coeffs;
        coeffs.reserve(n);
        for (const auto& node : nodes) {
            coeffs.push_back(node.second); // Inicjalizacja y-kami
        }

        for (int j = 1; j < n; ++j) {
            for (int i = n - 1; i >= j; --i) {
                coeffs[i] = (coeffs[i] - coeffs[i - 1]) / (nodes[i].first - nodes[i - j].first);
            }
        }
        return coeffs;
    }

    // Ewaluacja wielomianu Newtona za pomoc¹ schematu Hornera
    double evaluate_newton_polynomial(const std::vector<double>& coeffs, const std::vector<Point>& nodes, double x) {
        int n = coeffs.size();
        double result = coeffs[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            result = result * (x - nodes[i].first) + coeffs[i];
        }
        return result;
    }

} // Koniec anonimowej przestrzeni nazw

double newton_interpolation(const std::vector<Point>& nodes, double x) {
    if (nodes.empty()) {
        throw std::invalid_argument("Node vector cannot be empty.");
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = i + 1; j < nodes.size(); ++j) {
            if (nodes[i].first == nodes[j].first) {
                throw std::invalid_argument("Interpolation nodes must have unique x values.");
            }
        }
    }

    // Oblicz wspó³czynniki
    std::vector<double> coeffs = calculate_divided_differences(nodes);

    // Oblicz wartoœæ wielomianu
    return evaluate_newton_polynomial(coeffs, nodes, x);
}