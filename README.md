# Biblioteka Metod Numerycznych

## Opis Projektu
Niniejsza biblioteka C++ implementuje szereg popularnych metod numerycznych, poznanych w ramach laboratorium "Metody Numeryczne". Celem projektu jest dostarczenie zoptymalizowanych i przetestowanych implementacji do rozwiązywania typowych problemów matematycznych i inżynierskich.

**Kategorie funkcji:**
- Rozwiązywanie układów równań liniowych (np. eliminacja Gaussa)
- Interpolacja (np. Lagrange'a, Newtona)
- Aproksymacja (np. wielomianowa)
- Całkowanie numeryczne (np. metoda prostokątów, trapezów, Simpsona)
- Rozwiązywanie równań różniczkowych (np. Euler, Heun, midpoint, RK4)
- Rozwiązywanie równań nieliniowych (np. bisekcja, Newtona, siecznych, Regula Falsi)

Każda funkcja jest zaimplementowana z dbałością o poprawność numeryczną i obsługę błędów, rzucając odpowiednie wyjątki dla nieprawidłowych danych wejściowych.

## Wymagania
- Kompilator C++ (GCC/Clang) obsługujący standard C++17 lub nowszy.
- CMake (wersja 3.10 lub nowsza) do zarządzania procesem kompilacji.

## Instalacja i Budowa
Aby skompilować bibliotekę i przykłady, wykonaj następujące kroki:

1.  **Sklonuj repozytorium:**
    ```bash
    git clone [https://github.com/TwojaNazwaUzytkownika/nazwa_repozytorium.git](https://github.com/tatmer/biblioteka_numeryczna.git)
    cd nazwa_repozytorium

2.  **Utwórz katalog `build` i przejdź do niego:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Skonfiguruj projekt za pomocą CMake:**
    ```bash
    cmake ..
    ```

4.  **Zbuduj projekt:**
    ```bash
    cmake --build .
    ```
    Spowoduje to skompilowanie biblioteki (np. `libnumerix.a`), plików wykonywalnych testów oraz przykładów.

## Struktura Projektu
- `include/`: Zawiera pliki nagłówkowe (`.h`) z deklaracjami funkcji.
- `src/`: Zawiera pliki źródłowe (`.cpp`) z implementacjami funkcji.
- `tests/`: Zawiera testy jednostkowe dla każdej kategorii funkcji.
- `examples/`: Zawiera pliki demonstracyjne prezentujące użycie biblioteki.
- `CMakeLists.txt`: Główny plik konfiguracyjny CMake do budowania projektu.
- `README.md`: Ten plik.
  
## Przykłady Użycia
W katalogu `examples/` znajdziesz pliki `.cpp` demonstrujące użycie poszczególnych modułów biblioteki. Możesz uruchomić je z katalogu `build` po skompilowaniu projektu (np. `cmake --build .`).

### Rozwiązywanie równań nieliniowych (`example_root_finding`)
Ten przykład pokazuje, jak używać metod bisekcji, Newtona, siecznych i Regula Falsi do znajdowania pierwiastków różnych funkcji.
```bash
./example_root_finding

### Testowanie
Aby uruchomić wszystkie testy jednostkowe i upewnić się, że biblioteka działa poprawnie, wykonaj następujące polecenie z katalogu `build`:
```bash
ctest
