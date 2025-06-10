#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <utility> // dla std::pair

// Definicja typu dla punktu (x, y)
using Point = std::pair<double, double>;

/**
 * @file interpolation.h
 * @brief Deklaracje funkcji do interpolacji.
 */

 /**
  * @brief Oblicza wartoœæ wielomianu interpolacyjnego Lagrange'a w danym punkcie.
  * @param nodes Wektor punktów (wêz³ów interpolacji).
  * @param x Punkt, w którym ma byæ obliczona wartoœæ wielomianu.
  * @return Wartoœæ wielomianu w punkcie x.
  */
double lagrange_interpolation(const std::vector<Point>& nodes, double x);

/**
 * @brief Oblicza wartoœæ wielomianu interpolacyjnego Newtona w danym punkcie.
 *
 * Funkcja najpierw oblicza wspó³czynniki wielomianu (ilorazy ró¿nicowe),
 * a nastêpnie ewaluuje wielomian w punkcie x przy u¿yciu schematu Hornera.
 *
 * @param nodes Wektor punktów (wêz³ów interpolacji).
 * @param x Punkt, w którym ma byæ obliczona wartoœæ wielomianu.
 * @return Wartoœæ wielomianu w punkcie x.
 */
double newton_interpolation(const std::vector<Point>& nodes, double x);

#endif // INTERPOLATION_H