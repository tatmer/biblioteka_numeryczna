#include "nonlinear_equations.h" // Zakładamy, że zawiera deklaracje funkcji i np. IterationResult
#include <functional>             // Dla std::function
#include <cmath>                  // Dla std::abs, std::isnan, std::min
#include <limits>                 // Dla std::numeric_limits
#include <stdexcept>              // Dla std::invalid_argument, std::runtime_error
#include <vector>                 // Dla std::vector
#include <utility>                // Dla std::pair

// Prywatna funkcja pomocnicza do numerycznego obliczania pochodnej
// Umieszczona w anonimowej przestrzeni nazw, aby nie była widoczna poza tym plikiem
namespace {
    double numeric_derivative(std::function<double(double)> f, double x, double h = 1e-7) {
        if (h <= 0) {
            throw std::invalid_argument("Derivative step 'h' must be positive.");
        }
        double fx_plus_h = f(x + h);
        double fx_minus_h = f(x - h);

        if (std::isnan(fx_plus_h) || std::isnan(fx_minus_h)) {
            throw std::runtime_error("Function returned NaN during numeric derivative calculation (f(x+h) or f(x-h) is NaN).");
        }
        return (fx_plus_h - fx_minus_h) / (2 * h);
    }
}

double bisection_method(std::function<double(double)> func, double a, double b, double tolerance, int max_iterations) {
    if (tolerance <= 0.0) {
        throw std::invalid_argument("Tolerance must be positive for bisection method.");
    }
    if (max_iterations <= 0) {
        throw std::invalid_argument("Maximum iterations must be positive for bisection method.");
    }
    if (a >= b) {
        throw std::invalid_argument("Interval [a, b] must have a < b for bisection method.");
    }

    double fa = func(a);
    double fb = func(b);

    if (std::isnan(fa) || std::isnan(fb)) {
        throw std::runtime_error("Function returned NaN at one of the initial interval endpoints for bisection method.");
    }

    if (fa * fb >= 0) {
        throw std::invalid_argument("f(a) and f(b) must have opposite signs for bisection method.");
    }

    double c = a;
    for (int i = 0; i < max_iterations; ++i) {
        c = (a + b) / 2;
        double fc = func(c);

        if (std::isnan(fc)) {
            throw std::runtime_error("Function returned NaN during bisection method iteration.");
        }

        if (std::abs(fc) < tolerance || std::abs(b - a) < tolerance) {
            return c;
        }
        if (fa * fc < 0) {
            b = c;
            // fa pozostaje bez zmian
        }
        else {
            a = c;
            // fb pozostaje bez zmian
        }
        // Wartości funkcji fa i fb powinny być aktualizowane, jeśli a lub b się zmienia.
        // W metodzie bisekcji, fa i fb powinny zawsze utrzymywać przeciwny znak,
        // więc nie muszą być ponownie obliczane, chyba że zmieniają się 'a' lub 'b'.
        // Jednak dla ścisłości i bezpieczeństwa, można je zaktualizować.
        // fa = func(a); // Można odkomentować, jeśli są wątpliwości
        // fb = func(b); // Można odkomentować, jeśli są wątpliwości
    }
    throw std::runtime_error("Bisection method did not converge within the maximum number of iterations.");
}

double newton_method(std::function<double(double)> func, double x0, double tolerance, int max_iterations) {
    if (tolerance <= 0.0) {
        throw std::invalid_argument("Tolerance must be positive for Newton's method.");
    }
    if (max_iterations <= 0) {
        throw std::invalid_argument("Maximum iterations must be positive for Newton's method.");
    }

    double x_curr = x0;
    for (int i = 0; i < max_iterations; ++i) {
        double fx = func(x_curr);
        if (std::isnan(fx)) {
            throw std::runtime_error("Function returned NaN during Newton's method iteration (f(x_curr) is NaN).");
        }

        double dfx = numeric_derivative(func, x_curr); // Wywołanie pomocniczej funkcji pochodnej
        if (std::isnan(dfx)) {
             throw std::runtime_error("Derivative returned NaN during Newton's method iteration (df(x_curr) is NaN).");
        }

        // Sprawdzenie, czy pochodna jest bliska zeru, aby uniknąć dzielenia przez zero
        if (std::abs(dfx) < std::numeric_limits<double>::epsilon() * 100) {
            throw std::runtime_error("Newton's method: Derivative is too close to zero, cannot proceed.");
        }

        double x_next = x_curr - fx / dfx;

        if (std::abs(x_next - x_curr) < tolerance) {
            return x_next;
        }
        x_curr = x_next;
    }
    throw std::runtime_error("Newton's method did not converge within the maximum number of iterations.");
}

double secant_method(std::function<double(double)> func, double x0, double x1, double tolerance, int max_iterations) {
    if (tolerance <= 0.0) {
        throw std::invalid_argument("Tolerance must be positive for Secant method.");
    }
    if (max_iterations <= 0) {
        throw std::invalid_argument("Maximum iterations must be positive for Secant method.");
    }
    // Sprawdzenie, czy początkowe punkty są zbyt blisko siebie
    if (std::abs(x1 - x0) < std::numeric_limits<double>::epsilon() * 100) {
        throw std::invalid_argument("Secant method: Initial points x0 and x1 are too close.");
    }

    double fx0 = func(x0);
    double fx1 = func(x1);

    if (std::isnan(fx0) || std::isnan(fx1)) {
        throw std::runtime_error("Function returned NaN at one of the initial points for Secant method.");
    }

    for (int i = 0; i < max_iterations; ++i) {
        // Uniknięcie dzielenia przez zero, jeśli f(x1) - f(x0) jest zbyt małe
        if (std::abs(fx1 - fx0) < std::numeric_limits<double>::epsilon() * 100) {
            throw std::runtime_error("Secant method: Difference f(x1) - f(x0) is too small, cannot proceed.");
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        double fx2 = func(x2);

        if (std::isnan(x2) || std::isnan(fx2)) {
            throw std::runtime_error("Secant method: Iteration produced NaN value.");
        }

        if (std::abs(x2 - x1) < tolerance) {
            return x2;
        }

        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = fx2;
    }
    throw std::runtime_error("Secant method did not converge within the maximum number of iterations.");
}

// Funkcja Regula Falsi, z uwzględnieniem historii iteracji
double regula_falsi(
    std::function<double(double)> func, double a, double b,
    double tolerance_fx, double tolerance_dx, int max_iterations,
    std::vector<IterationResult>* history) // Zakładamy, że IterationResult jest zdefiniowane w nonlinear_equations.h
{
    // Walidacje parametrów wejściowych
    if (tolerance_fx <= 0.0) {
        throw std::invalid_argument("Tolerance_fx must be positive for Regula Falsi.");
    }
    if (tolerance_dx <= 0.0) {
        throw std::invalid_argument("Tolerance_dx must be positive for Regula Falsi.");
    }
    if (max_iterations <= 0) {
        throw std::invalid_argument("Maximum iterations must be positive for Regula Falsi.");
    }
    if (a >= b) {
        throw std::invalid_argument("Interval [a, b] must have a < b for Regula Falsi.");
    }

    if (history) history->clear(); // Wyczyść historię na początku

    double fa = func(a);
    double fb = func(b);

    if (std::isnan(fa) || std::isnan(fb)) {
        throw std::runtime_error("Regula Falsi: Function returned NaN at one of the initial interval endpoints.");
    }

    if (fa * fb >= 0) {
        throw std::invalid_argument("f(a) and f(b) must have opposite signs for Regula Falsi.");
    }

    double x_curr = a, x_prev = std::numeric_limits<double>::quiet_NaN();
    double fx_curr;

    for (int i = 0; i < max_iterations; ++i) {
        x_prev = x_curr;
            
        // Sprawdzenie, czy mianownik jest bliski zeru, aby uniknąć dzielenia przez zero
        if (std::abs(fb - fa) < std::numeric_limits<double>::epsilon() * 100) {
            throw std::runtime_error("Regula Falsi: Difference f(b) - f(a) is too small, cannot proceed.");
        }

        x_curr = (a * fb - b * fa) / (fb - fa);
        fx_curr = func(x_curr);

        if (std::isnan(x_curr) || std::isnan(fx_curr)) {
            throw std::runtime_error("Regula Falsi: Iteration produced NaN value.");
        }

        double error = std::abs(x_curr - x_prev);

        if (history) {
            history->push_back({i, x_curr, fx_curr, error});
        }
            
        if (std::abs(fx_curr) < tolerance_fx || error < tolerance_dx) {
            return x_curr;
        }

        if (fa * fx_curr < 0) {
            b = x_curr;
            fb = fx_curr;
        } else {
            a = x_curr;
            fa = fx_curr;
        }
    }
    throw std::runtime_error("Regula Falsi did not converge within the maximum number of iterations.");
}

std::vector<std::pair<double, double>> find_root_intervals(std::function<double(double)> func, double a, double b, double step) {
    if (step <= 0.0) {
        throw std::invalid_argument("Step size must be positive for find_root_intervals.");
    }
    if (a >= b) {
        throw std::invalid_argument("Start of interval must be less than end for find_root_intervals.");
    }

    std::vector<std::pair<double, double>> intervals;
    double x1 = a;
    double y1 = func(x1); // Oblicz początkową wartość y1

    // Możesz dodać sprawdzenie, czy y1 jest NaN i odpowiednio zareagować,
    // np. przesunąć x1 do pierwszego miejsca, gdzie funkcja jest poprawna.
    // Na razie zakładamy, że func(a) jest poprawne lub obsłużone przez wywołującego.

    while (x1 < b) {
        double x2 = std::min(x1 + step, b);
        double y2 = func(x2);

        if (std::isnan(y1) || std::isnan(y2)) {
            // Jeśli którakolwiek wartość jest NaN, nie możemy sprawdzić zmiany znaku.
            // Po prostu przejdź do następnego interwału.
            // Możesz też rozważyć rzucenie wyjątku, jeśli NaN jest uważane za krytyczny błąd.
        } else if (y1 * y2 < 0) {
            intervals.push_back({ x1, x2 });
        }
        x1 = x2;
        y1 = y2; // Zaktualizuj y1 na potrzeby następnej iteracji
        if (x1 == b) break; // Zakończ, jeśli osiągnęliśmy koniec przedziału
    }
    return intervals;
}