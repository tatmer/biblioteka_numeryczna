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
  * @brief Oblicza warto�� wielomianu interpolacyjnego Lagrange'a w danym punkcie.
  * @param nodes Wektor punkt�w (w�z��w interpolacji).
  * @param x Punkt, w kt�rym ma by� obliczona warto�� wielomianu.
  * @return Warto�� wielomianu w punkcie x.
  */
double lagrange_interpolation(const std::vector<Point>& nodes, double x);

/**
 * @brief Oblicza warto�� wielomianu interpolacyjnego Newtona w danym punkcie.
 *
 * Funkcja najpierw oblicza wsp�czynniki wielomianu (ilorazy r�nicowe),
 * a nast�pnie ewaluuje wielomian w punkcie x przy u�yciu schematu Hornera.
 *
 * @param nodes Wektor punkt�w (w�z��w interpolacji).
 * @param x Punkt, w kt�rym ma by� obliczona warto�� wielomianu.
 * @return Warto�� wielomianu w punkcie x.
 */
double newton_interpolation(const std::vector<Point>& nodes, double x);

#endif // INTERPOLATION_H