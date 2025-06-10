#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <functional>
#include <vector>

/**
 * @file approximation.h
 * @brief Deklaracje funkcji do aproksymacji.
 */

/**
 * @brief Aproksymuje funkcję wielomianem metodą najmniejszych kwadratów.
 *
 * Funkcja buduje układ równań liniowych, którego rozwiązaniem są współczynniki
 * wielomianu aproksymującego. Całki w macierzy układu są liczone numerycznie.
 *
 * @param func Funkcja do aproksymacji.
 * @param degree Stopień wielomianu aproksymującego.
 * @param a Początek przedziału aproksymacji.
 * @param b Koniec przedziału aproksymacji.
 * @return Wektor współczynników wielomianu [a0, a1, ..., a_degree].
 */
std::vector<double> polynomial_approximation(std::function<double(double)> func, int degree, double a, double b);

#endif // APPROXIMATION_H