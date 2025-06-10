#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdexcept> // Niezbędne do obsługi wyjątków
#include "nonlinear_equations.h" // Używamy naszej biblioteki

// Stała pi do użytku w f3
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

// Funkcja pomocnicza do numerycznego wyliczania pochodnej (dla testów Newtona)
// Ponieważ oryginalny 'newton_method' nie przyjmuje 'deriv_func', to jest konieczne,
// jeśli chcielibyśmy przetestować scenariusze z problematyczną pochodną.
// Jednak dla testów, które już masz, 'newton_method' używa tylko 'f', więc
// ten 'df' nie jest bezpośrednio używany w teście 'newton_method'.
// Zostawiam to jako przypomnienie, że Newton faktycznie wymaga pochodnej.
double numerical_derivative(std::function<double(double)> func, double x, double h = 1e-6) {
    return (func(x + h) - func(x - h)) / (2 * h);
}


int main() {
    std::vector<std::function<double(double)>> functions = { f1, f2, f3 };
    std::vector<std::string> names = { "f1", "f2", "f3" };

    std::cout << "--- Example: Comparison of Root-Finding Methods ---" << std::endl;
    std::cout << std::fixed << std::setprecision(8);

    // Parametry zbieżności
    double tolerance = 1e-7;
    int max_iter = 100;

    for (size_t i = 0; i < functions.size(); ++i) {
        auto& f = functions[i];
        std::cout << "\n=================================================" << std::endl;
        std::cout << "==== Funkcja " << names[i] << " (przedział [-5, 5]) ====" << std::endl;
        std::cout << "=================================================" << std::endl;

        // Znajdź przedziały, w których mogą istnieć pierwiastki
        auto intervals = find_root_intervals(f, -5.0, 5.0, 0.2);

        if (intervals.empty()) {
            std::cout << "Nie znaleziono przedzialow ze zmiana znaku." << std::endl;
            continue;
        }

        for (const auto& interval : intervals) {
            double a = interval.first;
            double b = interval.second;
            std::cout << "\n--- Przedzial [" << a << ", " << b << "] ---" << std::endl;

            // Użyjemy wyniku z bisekcji jako referencji do porównania błędów
            double root_ref = NAN;

            // Metoda Bisekcji
            try {
                root_ref = bisection_method(f, a, b, tolerance, max_iter);
                std::cout << "Bisekcja:       " << root_ref << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Bisekcja:       Blad - " << e.what() << std::endl;
                continue; // Jeśli bisekcja zawiedzie, nie ma sensu porównywać
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
                // Newtona, tak jak jest zadeklarowana w Twoim nagłówku, nie przyjmuje funkcji pochodnej.
                // Zakładamy, że albo pochodna jest obliczana numerycznie wewnętrznie, albo
                // ta wersja `newton_method` wymaga, aby funkcja `f` była taką, dla której
                // pochodna jest znana i wbudowana w logikę (co jest nietypowe dla ogólnej biblioteki).
                // Jeśli Twój 'newton_method' faktycznie potrzebuje pochodnej jako argumentu,
                // musiałbyś zmienić jego deklarację i wywołanie.
                // W tym przykładzie, aby zademonstrować błąd, będę polegał na tym, że
                // Twoja wewnętrzna implementacja 'newton_method' sprawdzi problematyczne scenariusze.
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

    // --- Błędne testy ---
    std::cout << "\n=================================================" << std::endl;
    std::cout << "==== Błędne Testy: Niepoprawne Dane Wejściowe ====" << std::endl;
    std::cout << "=================================================" << std::endl;

    // Test 1: Bisekcja i Regula Falsi - brak zmiany znaku w przedziale
    // Dla f1(x) = log(x + 1.0) - (1.0 / (x + 3.0))
    // Wiemy, że f1(0.5) < 0 i f1(1.0) < 0. Nie ma zmiany znaku.
    double a_no_sign_change = 0.5;
    double b_no_sign_change = 1.0;
    std::cout << "\n--- Brak zmiany znaku w przedziale [" << a_no_sign_change << ", " << b_no_sign_change << "] dla f1 ---" << std::endl;

    std::cout << "Test: Bisekcja z brakiem zmiany znaku: ";
    try {
        double result = bisection_method(f1, a_no_sign_change, b_no_sign_change, tolerance, max_iter);
        std::cout << "Otrzymano nieoczekiwany wynik: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Złapano oczekiwany błąd: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Złapano nieoczekiwany typ błędu: " << e.what() << std::endl;
    }

    std::cout << "Test: Regula Falsi z brakiem zmiany znaku: ";
    try {
        double result = regula_falsi(f1, a_no_sign_change, b_no_sign_change, tolerance, tolerance, max_iter);
        std::cout << "Otrzymano nieoczekiwany wynik: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Złapano oczekiwany błąd: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Złapano nieoczekiwany typ błędu: " << e.what() << std::endl;
    }

    // Test 2: Metoda Newtona - pochodna bliska zeru w punkcie startowym
    // Spróbujemy wywołać błąd dla funkcji, gdzie pochodna może być problematyczna.
    // Bez dostępu do dokładnej pochodnej, musimy wybrać punkt, gdzie f'(x) jest bliskie 0.
    // Jeśli Twoja implementacja `newton_method` oblicza pochodną numerycznie,
    // to ten test będzie polegał na tym, że wewnętrzne sprawdzenie pochodnej zadziała.
    double x0_newton_bad_deriv = -4.0; // Przykładowy punkt, gdzie f3 ma problem z pochodną (f3 ma asymptotę pionową przy -4)
    std::cout << "\n--- Newtona: Pochodna bliska zeru (lub problematyczny punkt) dla f3 w x0 = " << x0_newton_bad_deriv << " ---" << std::endl;
    try {
        double result = newton_method(f3, x0_newton_bad_deriv, tolerance, max_iter);
        std::cout << "Otrzymano nieoczekiwany wynik: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Złapano oczekiwany błąd: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Złapano nieoczekiwany typ błędu: " << e.what() << std::endl;
    }

    // Test 3: Metoda Siecznych - identyczne punkty startowe
    double x0_secant_same = 2.0;
    double x1_secant_same = 2.0;
    std::cout << "\n--- Siecznych: Identyczne punkty startowe [" << x0_secant_same << ", " << x1_secant_same << "] ---" << std::endl;
    try {
        double result = secant_method(f1, x0_secant_same, x1_secant_same, tolerance, max_iter);
        std::cout << "Otrzymano nieoczekiwany wynik: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Złapano oczekiwany błąd: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Złapano nieoczekiwany typ błędu: " << e.what() << std::endl;
    }

    // Test 4: Find Root Intervals - niepoprawny krok
    double bad_step = 0.0;
    std::cout << "\n--- find_root_intervals: Niepoprawny krok = " << bad_step << " ---" << std::endl;
    try {
        auto intervals_err = find_root_intervals(f1, -5.0, 5.0, bad_step);
        std::cout << "Otrzymano nieoczekiwany wynik (liczba przedziałów: " << intervals_err.size() << ")" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Złapano oczekiwany błąd: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Złapano nieoczekiwany typ błędu: " << e.what() << std::endl;
    }

    return 0;
}