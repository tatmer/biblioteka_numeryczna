#ifndef NONLINEAR_EQUATIONS_H
#define NONLINEAR_EQUATIONS_H

#include <functional>
#include <vector>
#include <string>
#include <utility> // dla std::pair

/**
 * @file nonlinear_equations.h
 * @brief Deklaracje funkcji do rozwiązywania równań nieliniowych.
 */

 // Struktura przechowująca dane z jednej iteracji
struct IterationResult {
    int iteration_count;
    double root_approximation;
    double function_value;
    double relative_error;
};

// --- ISTNIEJĄCA FUNKCJA ---

/**
 * @brief Znajduje pierwiastek funkcji metodą fałszywej linii (Regula Falsi).
 */
double regula_falsi(
    std::function<double(double)> func, double a, double b,
    double tolerance_fx, double tolerance_dx, int max_iterations,
    std::vector<IterationResult>* history = nullptr);

// --- NOWE FUNKCJE ---

/**
 * @brief Znajduje pierwiastek funkcji metodą bisekcji.
 * @param tolerance Kryterium zbieżności dla szerokości przedziału |b - a|.
 * @param max_iterations Maksymalna liczba iteracji.
 * @return Przybliżenie pierwiastka. Rzuca wyjątek w razie błędu.
 */
double bisection_method(
    std::function<double(double)> func, double a, double b,
    double tolerance = 1e-7, int max_iterations = 100);

/**
 * @brief Znajduje pierwiastek funkcji metodą Newtona (stycznych).
 * @param x0 Punkt startowy.
 * @return Przybliżenie pierwiastka. Rzuca wyjątek w razie błędu.
 */
double newton_method(
    std::function<double(double)> func, double x0,
    double tolerance = 1e-7, int max_iterations = 100);

/**
 * @brief Znajduje pierwiastek funkcji metodą siecznych.
 * @param x0 Pierwszy punkt startowy.
 * @param x1 Drugi punkt startowy.
 * @return Przybliżenie pierwiastka. Rzuca wyjątek w razie błędu.
 */
double secant_method(
    std::function<double(double)> func, double x0, double x1,
    double tolerance = 1e-7, int max_iterations = 100);

/**
 * @brief Skanuje przedział w poszukiwaniu zmian znaku funkcji, wskazujących na istnienie pierwiastków.
 * @param a Początek przedziału.
 * @param b Koniec przedziału.
 * @param step Krok skanowania.
 * @return Wektor par (przedziałów) ze zmianą znaku.
 */
std::vector<std::pair<double, double>> find_root_intervals(
    std::function<double(double)> func, double a, double b, double step = 0.1);


#endif // NONLINEAR_EQUATIONS_H