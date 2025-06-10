#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "nonlinear_equations.h" // U¿ywamy naszej biblioteki

// Sta³a pi do u¿ytku w f3
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Funkcje testowe ---
double f1(double x) {
    if (x <= -1.0 || x == -3.0) return NAN; // log lub dzielenie przez 0
    return log(x + 1.0) - (1.0 / (x + 3.0));
}

double f2(double x) {
    if (x == 0.0) return NAN;
    return pow(x, 3.0) + 30.0 * cos(x) - (1.0 / x);
}

double f3(double x) {
    if (x == -2.0 || x == -4.0) return NAN;
    return sin(3.0 * M_PI * x) / (x + 2.0) + 1.0 / (x + 4.0);
}

int main() {
    std::vector<std::function<double(double)>> functions = { f1, f2, f3 };
    std::vector<std::string> names = { "f1", "f2", "f3" };

    std::cout << "--- Example: Comparison of Root-Finding Methods ---" << std::endl;
    std::cout << std::fixed << std::setprecision(8);

    // Parametry zbie¿noœci
    double tolerance = 1e-7;
    int max_iter = 100;

    for (size_t i = 0; i < functions.size(); ++i) {
        auto& f = functions[i];
        std::cout << "\n=================================================" << std::endl;
        std::cout << "==== Funkcja " << names[i] << " (przedzial [-5, 5]) ====" << std::endl;
        std::cout << "=================================================" << std::endl;

        // ZnajdŸ przedzia³y, w których mog¹ istnieæ pierwiastki
        auto intervals = find_root_intervals(f, -5.0, 5.0, 0.2);

        if (intervals.empty()) {
            std::cout << "Nie znaleziono przedzialow ze zmiana znaku." << std::endl;
            continue;
        }

        for (const auto& interval : intervals) {
            double a = interval.first;
            double b = interval.second;
            std::cout << "\n--- Przedzial [" << a << ", " << b << "] ---" << std::endl;

            // U¿yjemy wyniku z bisekcji jako referencji do porównania b³êdów
            double root_ref = NAN;

            // Metoda Bisekcji
            try {
                root_ref = bisection_method(f, a, b, tolerance, max_iter);
                std::cout << "Bisekcja:       " << root_ref << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Bisekcja:       Blad - " << e.what() << std::endl;
                continue; // Jeœli bisekcja zawiedzie, nie ma sensu porównywaæ
            }

            // Metoda Regula Falsi
            try {
                double root_rf = regula_falsi(f, a, b, tolerance, tolerance, max_iter);
                std::cout << "Regula Falsi:   " << root_rf << " (Blad vs Bisekcja: " << std::abs(root_rf - root_ref) << ")" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Regula Falsi:   Blad - " << e.what() << std::endl;
            }

            // Metoda Newtona
            try {
                double root_newt = newton_method(f, (a + b) / 2.0, tolerance, max_iter);
                std::cout << "Newtona:        " << root_newt << " (Blad vs Bisekcja: " << std::abs(root_newt - root_ref) << ")" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Newtona:        Blad - " << e.what() << std::endl;
            }

            // Metoda Siecznych
            try {
                double root_sec = secant_method(f, a, b, tolerance, max_iter);
                std::cout << "Siecznych:      " << root_sec << " (Blad vs Bisekcja: " << std::abs(root_sec - root_ref) << ")" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Siecznych:      Blad - " << e.what() << std::endl;
            }
        }
    }

    return 0;
}