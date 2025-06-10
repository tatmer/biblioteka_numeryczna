#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>
#include <string>

// Definicje typ�w dla czytelno�ci
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

/**
 * @file linear_algebra.h
 * @brief Deklaracje funkcji do rozwi�zywania uk�ad�w r�wna� liniowych.
 */

 /**
  * @brief Rozwi�zuje uk�ad r�wna� liniowych Ax = b metod� eliminacji Gaussa z pe�nym pivotowaniem.
  * @param A Macierz wsp�czynnik�w (b�dzie modyfikowana).
  * @param b Wektor wyraz�w wolnych (b�dzie modyfikowany).
  * @return Wektor rozwi�zania x.
  * @throws std::runtime_error je�li macierz jest osobliwa.
  */
Vector solve_gauss(Matrix A, Vector b);

/**
 * @brief Rozwi�zuje uk�ad r�wna� liniowych Ax = b przy u�yciu dekompozycji LU.
 *
 * Funkcja wewn�trznie wykonuje dekompozycj� LU macierzy A, a nast�pnie rozwi�zuje
 * dwa uk�ady tr�jk�tne: Lz = b' i Ux = z, gdzie b' to wektor b po przestawieniach.
 *
 * @param A Macierz wsp�czynnik�w.
 * @param b Wektor wyraz�w wolnych.
 * @return Wektor rozwi�zania x.
 * @throws std::runtime_error je�li macierz jest osobliwa.
 */
Vector solve_lu(Matrix A, Vector b);

#endif // LINEAR_ALGEBRA_H