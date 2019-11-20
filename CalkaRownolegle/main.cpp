#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

double f(double x) {
    return 4 / (1 + x * x);
}

int main() {
    auto n = omp_get_num_threads();
    vector<double> calka(n);
    vector<double> time(n);
    double a = 0;
    double b = 1;
    double dx = 0.000001;
    auto m = int((b - a) / dx);

    auto start = omp_get_wtime();
#pragma omp parallel
    {
        auto k = omp_get_thread_num();
        double w = 0;
        for (auto i = k; i < m; i += n) {
            w += f(a + i * dx) * dx;
        }
        calka[k]= w;
    }
    auto end = omp_get_wtime();

    cout << calka[0] << endl << "Czas: " << end - start;

    return 0;
}
