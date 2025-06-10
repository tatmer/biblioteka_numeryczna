#include <iostream>
#include <iomanip>
#include <cmath>
#include "differential_equations.h" // Use our library

// Constants for the cooling problem
const double T_start = 1198.0;   // Initial temperature
const double T_env = 0.0;        // Environment temperature (your beta was 0)
const double alpha = 98.0e-12;   // Stefan-Boltzmann constant factor

// The ODE function: dT/dt = f(t, T)
double cooling_ode(double t, double T) {
    // 't' is unused in this specific problem, but the signature is general
    (void)t; // Mark 't' as intentionally unused
    return -alpha * (pow(T, 4) - pow(T_env, 4));
}

int main() {
    std::cout << "--- Example: ODE Solvers (Cooling Problem) ---" << std::endl;

    double t0 = 0.0;
    double t_max = 1000.0;
    double h = 1.0;

    std::cout << "Solving ODE with step h = " << h << " up to t = " << t_max << std::endl;

    // Solve using RK4 method
    OdeResult result_rk4 = rk4_method(cooling_ode, T_start, t0, t_max, h);

    // Print a few values
    std::cout << "\n--- RK4 Method Results ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time (s)\tTemperature (K)" << std::endl;
    for (size_t i = 0; i < result_rk4.size(); i += 100) {
        std::cout << result_rk4[i].first << "\t\t" << result_rk4[i].second << std::endl;
    }

    return 0;
}