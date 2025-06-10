#ifndef DIFFERENTIAL_EQUATIONS_H
#define DIFFERENTIAL_EQUATIONS_H

#include <functional>
#include <vector>
#include <utility> // dla std::pair

/**
 * @file differential_equations.h
 * @brief Deklaracje funkcji do rozwiązywania równań różniczkowych zwyczajnych.
 */

// Definicja typu dla funkcji y' = f(t, y)
using OdeFunction = std::function<double(double t, double y)>;
// Definicja typu dla wektora wyników (pary czas, wartość)
using OdeResult = std::vector<std::pair<double, double>>;

/**
 * @brief Rozwiązuje równanie różniczkowe y'=f(t,y) metodą Eulera.
 * @param f Funkcja pochodnej.
 * @param y0 Wartość początkowa y(t0).
 * @param t0 Czas początkowy.
 * @param t_max Czas końcowy.
 * @param h Krok czasowy.
 * @return Wektor par (t, y) z rozwiązaniem.
 */
OdeResult euler_method(OdeFunction f, double y0, double t0, double t_max, double h);
OdeResult heun_method(OdeFunction f, double y0, double t0, double t_max, double h);
OdeResult midpoint_method(OdeFunction f, double y0, double t0, double t_max, double h);
OdeResult rk4_method(OdeFunction f, double y0, double t0, double t_max, double h);

#endif // DIFFERENTIAL_EQUATIONS_H