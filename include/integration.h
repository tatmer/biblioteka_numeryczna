#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>
#include <vector>

/**
 * @file integration.h
 * @brief Deklaracje funkcji do całkowania numerycznego.
 */

/**
 * @brief Oblicza całkę oznaczoną złożoną metodą prostokątów.
 * @param func Funkcja do całkowania, std::function<double(double)>.
 * @param a Dolna granica całkowania.
 * @param b Górna granica całkowania.
 * @param intervals Liczba podprzedziałów.
 * @return Przybliżona wartość całki.
 */
double rectangle_rule(std::function<double(double)> func, double a, double b, int intervals);

/**
 * @brief Oblicza całkę oznaczoną złożoną metodą trapezów.
 */
double trapezoid_rule(std::function<double(double)> func, double a, double b, int intervals);

/**
 * @brief Oblicza całkę oznaczoną złożoną metodą Simpsona.
 */
double simpson_rule(std::function<double(double)> func, double a, double b, int intervals);

/**
 * @brief Oblicza całkę oznaczoną złożoną kwadraturą Gaussa-Legendre'a.
 * @param nodes Liczba węzłów kwadratury (2, 3 lub 4).
 * @param subintervals Liczba podprzedziałów, na które dzielony jest główny przedział.
 */
double gauss_legendre_quadrature(std::function<double(double)> func, double a, double b, int nodes, int subintervals);

#endif // INTEGRATION_H