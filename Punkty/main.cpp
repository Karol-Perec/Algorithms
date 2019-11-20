#include <iostream>
#include <random>
#include <omp.h>

int main() {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_real_distribution<> distribution(-1, 1); // guaranteed unbiased
    auto howManyIterations = 100000000;

    double a = 1;
    int squarePoints = 0;
    int circlePoints = 0;

    auto start = omp_get_wtime();
    for (int i = 0; i < howManyIterations; i++) {
        auto x = distribution(rng);
        auto y = distribution(rng);

        if (x * x + y * y < a)
            circlePoints++;
        squarePoints++;
    }
    double pi = 4 * a * circlePoints / squarePoints;
    auto end = omp_get_wtime();

    std::cout << pi << std::endl << "Czas: " << end - start;
    return 0;
}