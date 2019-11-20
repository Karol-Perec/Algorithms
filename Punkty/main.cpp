#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

double f(double x) {
    return 4 / (1 + x * x);
}

int main() {

    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> random(0,2); // guaranteed unbiased

    auto random_integer = random(rng);

    auto start = omp_get_wtime();
    for (int i = 0; i < m; i++) {
        calka += f(a + i * dx) * dx;
    }
    auto end = omp_get_wtime();

    cout << calka << endl << "Czas: " << end - start;
    return 0;
}