#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept> // For std::invalid_argument
#include <cstdlib>   // For EXIT_FAILURE
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
    std::cout << "\n--- RK4 Method Results (Correct Case) ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time (s)\tTemperature (K)" << std::endl;
    for (size_t i = 0; i < result_rk4.size(); i += 100) { // Print every 100th point
        std::cout << result_rk4[i].first << "\t\t" << result_rk4[i].second << std::endl;
    }
    std::cout << "..." << std::endl;
    std::cout << result_rk4.back().first << "\t\t" << result_rk4.back().second << std::endl;


    // --- Erroneous Test Case: Invalid Step Size ---
    std::cout << "\n--- Erroneous Test: Invalid Step Size (h = 0.0) ---" << std::endl;
    double h_invalid_zero = 0.0;
    
    std::cout << "Attempting to solve with h = " << h_invalid_zero << ": ";
    try {
        OdeResult result_err_h = rk4_method(cooling_ode, T_start, t0, t_max, h_invalid_zero);
        // Jeśli ten kod zostanie osiągnięty, to test zakończył się niepowodzeniem (nie złapał błędu)
        std::cerr << "Test FAILED: Solver completed without expected error (invalid_argument) for h = 0.0." << std::endl;
        return EXIT_FAILURE; // Zakończ program z błędem
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Test PASSED: Caught expected error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Jeśli złapano inny typ wyjątku, to również jest błąd testu
        std::cerr << "Test FAILED: Caught unexpected error type: " << e.what() << std::endl;
        return EXIT_FAILURE; // Zakończ program z błędem
    }

    // --- Erroneous Test Case: Invalid Time Range ---
    std::cout << "\n--- Erroneous Test: Invalid Time Range (t_max < t0) ---" << std::endl;
    double t_max_invalid = -10.0; // t_max is less than t0

    std::cout << "Attempting to solve from t0=" << t0 << " to t_max=" << t_max_invalid << ": ";
    try {
        OdeResult result_err_range = rk4_method(cooling_ode, T_start, t0, t_max_invalid, h);
        // Jeśli ten kod zostanie osiągnięty, to test zakończył się niepowodzeniem (nie złapał błędu)
        std::cerr << "Test FAILED: Solver completed without expected error (invalid_argument) for t_max < t0." << std::endl;
        return EXIT_FAILURE; // Zakończ program z błędem
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Test PASSED: Caught expected error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Jeśli złapano inny typ wyjątku, to również jest błąd testu
        std::cerr << "Test FAILED: Caught unexpected error type: " << e.what() << std::endl;
        return EXIT_FAILURE; // Zakończ program z błędem
    }

    std::cout << "\nAll tests completed successfully." << std::endl;
    return EXIT_SUCCESS; // Zakończ program pomyślnie, jeśli wszystkie testy przeszły
}