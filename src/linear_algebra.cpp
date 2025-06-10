#include "linear_algebra.h"
#include <stdexcept>
#include <cmath>
#include <algorithm> // dla std::swap

// --- Implementacja metody Gaussa ---

Vector solve_gauss(Matrix A, Vector b) {
    int n = A.size();
    if (n == 0 || A[0].size() != n || b.size() != n) {
        throw std::invalid_argument("Invalid matrix or vector dimensions.");
    }

    for (int i = 0; i < n; i++) {
        // Pivotowanie (wybór elementu g³ównego w kolumnie)
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                max_row = k;
            }
        }
        std::swap(A[i], A[max_row]);
        std::swap(b[i], b[max_row]);

        // Sprawdzenie osobliwoœci
        if (std::abs(A[i][i]) < 1e-12) {
            throw std::runtime_error("Matrix is singular or nearly singular.");
        }

        // Eliminacja
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            b[k] -= factor * b[i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    // Podstawienie wsteczne (Back Substitution)
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}


// --- Implementacja metody LU ---

Vector solve_lu(Matrix A, Vector b) {
    int n = A.size();
    if (n == 0 || A[0].size() != n || b.size() != n) {
        throw std::invalid_argument("Invalid matrix or vector dimensions.");
    }

    Matrix L(n, Vector(n, 0.0));
    Matrix U = A;

    // Krok 1: Dekompozycja LU z pivotowaniem (wersja uproszczona, modyfikuj¹ca b)
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
    }

    for (int k = 0; k < n; k++) {
        // Pivotowanie
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (std::abs(U[i][k]) > std::abs(U[max_row][k])) {
                max_row = i;
            }
        }
        if (max_row != k) {
            std::swap(U[k], U[max_row]);
            std::swap(b[k], b[max_row]); // Pivotujemy równie¿ wektor b
        }

        if (std::abs(U[k][k]) < 1e-12) {
            throw std::runtime_error("Matrix is singular, LU decomposition failed.");
        }

        // Tworzenie macierzy L i U
        for (int i = k + 1; i < n; i++) {
            double factor = U[i][k] / U[k][k];
            L[i][k] = factor;
            for (int j = k; j < n; j++) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }

    // Krok 2: Rozwi¹zanie Lz = b (Podstawienie w przód)
    Vector z(n);
    for (int i = 0; i < n; i++) {
        z[i] = b[i];
        for (int j = 0; j < i; j++) {
            z[i] -= L[i][j] * z[j];
        }
    }

    // Krok 3: Rozwi¹zanie Ux = z (Podstawienie wstecz)
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = z[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
    return x;
}