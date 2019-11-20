#include <iostream>
#include <omp.h>

using namespace std;

double f(double x) {
    return 4 / (1 + x * x);
}

int main() {
    double calka = 0;
    double a = 0;
    double b = 1;
    double dx = 0.000001;
    auto m = int((b - a) / dx);

    auto start = omp_get_wtime();
#pragma omp parallel for reduction (+:calka)
    for (auto i = 0; i < m; i++) {
        calka += f(a + i * dx) * dx;
    }
    auto end = omp_get_wtime();

    cout << calka << endl << "Czas: " << end - start;

    return 0;
}
