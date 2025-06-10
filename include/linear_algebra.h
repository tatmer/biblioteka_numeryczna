#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>
#include <string>

// Definicje typów dla czytelnoœci
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

/**
 * @file linear_algebra.h
 * @brief Deklaracje funkcji do rozwi¹zywania uk³adów równañ liniowych.
 */

 /**
  * @brief Rozwi¹zuje uk³ad równañ liniowych Ax = b metod¹ eliminacji Gaussa z pe³nym pivotowaniem.
  * @param A Macierz wspó³czynników (bêdzie modyfikowana).
  * @param b Wektor wyrazów wolnych (bêdzie modyfikowany).
  * @return Wektor rozwi¹zania x.
  * @throws std::runtime_error jeœli macierz jest osobliwa.
  */
Vector solve_gauss(Matrix A, Vector b);

/**
 * @brief Rozwi¹zuje uk³ad równañ liniowych Ax = b przy u¿yciu dekompozycji LU.
 *
 * Funkcja wewnêtrznie wykonuje dekompozycjê LU macierzy A, a nastêpnie rozwi¹zuje
 * dwa uk³ady trójk¹tne: Lz = b' i Ux = z, gdzie b' to wektor b po przestawieniach.
 *
 * @param A Macierz wspó³czynników.
 * @param b Wektor wyrazów wolnych.
 * @return Wektor rozwi¹zania x.
 * @throws std::runtime_error jeœli macierz jest osobliwa.
 */
Vector solve_lu(Matrix A, Vector b);

#endif // LINEAR_ALGEBRA_H