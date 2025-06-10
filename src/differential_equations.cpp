#include "differential_equations.h" // Zakładamy, że zawiera deklaracje funkcji, OdeFunction i OdeResult
#include <functional>             // Dla std::function
#include <vector>                 // Dla std::vector
#include <stdexcept>              // Dla std::invalid_argument, std::runtime_error
#include <cmath>                  // Dla std::abs, std::isnan
#include <limits>                 // Dla std::numeric_limits (do porównań zmiennoprzecinkowych)
#include <utility>                // Dla std::pair (jeśli OdeResult używa std::vector<std::pair<double, double>>)
#include <algorithm>              // Dla std::min

// Zakładamy, że OdeFunction jest zdefiniowane jako:
// using OdeFunction = std::function<double(double, double)>;
//
// Zakładamy, że OdeResult jest zdefiniowane jako:
// using OdeResult = std::vector<std::pair<double, double>>;
// lub podobna struktura, która obsługuje emplace_back(double, double).

OdeResult euler_method(OdeFunction f, double y0, double t0, double t_max, double h) {
    // --- WALIDACJE WEJŚCIOWE ---
    if (h <= 0.0) {
        throw std::invalid_argument("Euler method: Step size 'h' must be positive.");
    }
    if (t_max < t0) {
        throw std::invalid_argument("Euler method: End time 't_max' cannot be less than start time 't0'.");
    }

    OdeResult result;
    double y = y0;
    // Iteracja, z uwzględnieniem tolerancji zmiennoprzecinkowej dla t_max
    for (double t = t0; t <= t_max + std::numeric_limits<double>::epsilon() * std::abs(t_max); t += h) {
        // Clamp t to t_max for the last point if it overshoots slightly
        double current_t = std::min(t, t_max);

        result.emplace_back(current_t, y);

        // Obliczenia K, z walidacją NaN
        double k = f(current_t, y);
        if (std::isnan(k)) {
            throw std::runtime_error("Euler method: ODE function returned NaN during iteration (k is NaN).");
        }
        y += h * k;
    }
    return result;
}

OdeResult heun_method(OdeFunction f, double y0, double t0, double t_max, double h) {
    // --- WALIDACJE WEJŚCIOWE ---
    if (h <= 0.0) {
        throw std::invalid_argument("Heun method: Step size 'h' must be positive.");
    }
    if (t_max < t0) {
        throw std::invalid_argument("Heun method: End time 't_max' cannot be less than start time 't0'.");
    }

    OdeResult result;
    double y = y0;
    // Iteracja, z uwzględnieniem tolerancji zmiennoprzecinkowej dla t_max
    for (double t = t0; t <= t_max + std::numeric_limits<double>::epsilon() * std::abs(t_max); t += h) {
        double current_t = std::min(t, t_max);

        result.emplace_back(current_t, y);

        // Obliczenia K1 i K2, z walidacją NaN
        double k1 = f(current_t, y);
        if (std::isnan(k1)) {
            throw std::runtime_error("Heun method: ODE function returned NaN for k1 during iteration.");
        }
        double k2 = f(current_t + h, y + h * k1);
        if (std::isnan(k2)) {
            throw std::runtime_error("Heun method: ODE function returned NaN for k2 during iteration.");
        }
        y += h * 0.5 * (k1 + k2);
    }
    return result;
}

OdeResult midpoint_method(OdeFunction f, double y0, double t0, double t_max, double h) {
    // --- WALIDACJE WEJŚCIOWE ---
    if (h <= 0.0) {
        throw std::invalid_argument("Midpoint method: Step size 'h' must be positive.");
    }
    if (t_max < t0) {
        throw std::invalid_argument("Midpoint method: End time 't_max' cannot be less than start time 't0'.");
    }

    OdeResult result;
    double y = y0;
    // Iteracja, z uwzględnieniem tolerancji zmiennoprzecinkowej dla t_max
    for (double t = t0; t <= t_max + std::numeric_limits<double>::epsilon() * std::abs(t_max); t += h) {
        double current_t = std::min(t, t_max);

        result.emplace_back(current_t, y);

        // Obliczenia K1 i K2, z walidacją NaN
        double k1 = f(current_t, y);
        if (std::isnan(k1)) {
            throw std::runtime_error("Midpoint method: ODE function returned NaN for k1 during iteration.");
        }
        double k2 = f(current_t + 0.5 * h, y + 0.5 * h * k1);
        if (std::isnan(k2)) {
            throw std::runtime_error("Midpoint method: ODE function returned NaN for k2 during iteration.");
        }
        y += h * k2;
    }
    return result;
}

OdeResult rk4_method(OdeFunction f, double y0, double t0, double t_max, double h) {
    // --- WALIDACJE WEJŚCIOWE (PRZED PĘTLĄ) ---
    if (h <= 0.0) {
        throw std::invalid_argument("RK4 method: Step size 'h' must be positive.");
    }
    if (t_max < t0) {
        throw std::invalid_argument("RK4 method: End time 't_max' cannot be less than start time 't0'.");
    }

    OdeResult result;
    double y = y0;
    // Iteracja, z uwzględnieniem tolerancji zmiennoprzecinkowej dla t_max
    for (double t = t0; t <= t_max + std::numeric_limits<double>::epsilon() * std::abs(t_max); t += h) {
        // Zapewnienie, że bieżący czas nie przekracza t_max, jeśli h nie dzieli równo
        double current_t = std::min(t, t_max);
        
        result.emplace_back(current_t, y);

        // Obliczenia K1, K2, K3, K4 z walidacją NaN
        double k1 = f(current_t, y);
        if (std::isnan(k1)) {
            throw std::runtime_error("RK4 method: ODE function returned NaN for k1 during iteration.");
        }
        double k2 = f(current_t + 0.5 * h, y + 0.5 * h * k1);
        if (std::isnan(k2)) {
            throw std::runtime_error("RK4 method: ODE function returned NaN for k2 during iteration.");
        }
        double k3 = f(current_t + 0.5 * h, y + 0.5 * h * k2);
        if (std::isnan(k3)) {
            throw std::runtime_error("RK4 method: ODE function returned NaN for k3 during iteration.");
        }
        double k4 = f(current_t + h, y + h * k3);
        if (std::isnan(k4)) {
            throw std::runtime_error("RK4 method: ODE function returned NaN for k4 during iteration.");
        }
        y += h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
    }
    return result;
}