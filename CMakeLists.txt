# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(NumericalLibrary CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Definicja Biblioteki ---
# Automatycznie znajdź wszystkie pliki źródłowe w katalogu src/
file(GLOB SOURCES 
    "src/integration.cpp"
    "src/nonlinear_equations.cpp"
    "src/differential_equations.cpp"
    "src/approximation.cpp"
    "src/linear_algebra.cpp"
    "src/interpolation.cpp"
)

# Stwórz bibliotekę statyczną o nazwie "numerix" z znalezionych plików
add_library(numerix STATIC ${SOURCES})

# Określ, że pliki nagłówkowe biblioteki są w katalogu "include"
target_include_directories(numerix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# --- Definicja Przykładów (KAŻDY JAKO OSOBNY PROGRAM) ---

# Przykład 1: Całkowanie
add_executable(example_integration examples/example_integration.cpp)
target_link_libraries(example_integration PRIVATE numerix)

# Przykład 2: Równania nieliniowe
add_executable(example_root_finding examples/example_root_finding.cpp)
target_link_libraries(example_root_finding PRIVATE numerix)

# Przykład 3: Równania różniczkowe
add_executable(example_ode examples/example_ode.cpp)
target_link_libraries(example_ode PRIVATE numerix)

# Przykład 4: Aproksymacja
add_executable(example_approximation examples/example_approximation.cpp)
target_link_libraries(example_approximation PRIVATE numerix)

# Przykład 5: Algebra liniowa
add_executable(example_linear_algebra examples/example_linear_algebra.cpp)
target_link_libraries(example_linear_algebra PRIVATE numerix)

# Przykład 6: Interpolacja
add_executable(example_interpolation examples/example_interpolation.cpp)
target_link_libraries(example_interpolation PRIVATE numerix)


# --- Definicja Testów ---
# Włącz obsługę testowania (CTest)
enable_testing()

# Test 1: Aproksymacja
add_executable(test_approximation tests/test_approximation.cpp)
target_link_libraries(test_approximation PRIVATE numerix)
add_test(NAME test_approximation COMMAND test_approximation)

# Test 2: Całkowanie
add_executable(test_integration tests/test_integration.cpp)
target_link_libraries(test_integration PRIVATE numerix)
add_test(NAME test_integration COMMAND test_integration)

# Test 3: Interpolacja
add_executable(test_interpolation tests/test_interpolation.cpp)
target_link_libraries(test_interpolation PRIVATE numerix)
add_test(NAME test_interpolation COMMAND test_interpolation)

# Test 4: Algebra liniowa
add_executable(test_linear_algebra tests/test_linear_algebra.cpp)
target_link_libraries(test_linear_algebra PRIVATE numerix)
add_test(NAME test_linear_algebra COMMAND test_linear_algebra)

# Test 5: Równania różniczkowe (ODE)
add_executable(test_ode tests/test_ode.cpp)
target_link_libraries(test_ode PRIVATE numerix)
add_test(NAME test_ode COMMAND test_ode)

# Test 6: Równania nieliniowe (Root Finding)
add_executable(test_root_finding tests/test_root_finding.cpp)
target_link_libraries(test_root_finding PRIVATE numerix)
add_test(NAME test_root_finding COMMAND test_root_finding)


# Informacje dla użytkownika
message(STATUS "Library 'numerix', examples, and tests configured correctly.")
message(STATUS "To build, run 'make' or your build system's equivalent.")
message(STATUS "To run tests, execute 'ctest' in the build directory.")