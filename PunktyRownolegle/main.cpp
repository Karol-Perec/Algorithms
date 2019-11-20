#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include <iostream>
#include <random>
#include <omp.h>
#include <cmath>
#include <time.h>
#include <cstdlib>

int main() {
    int howManyIterations = 100000000;
    double a = 1;
    int n = omp_get_max_threads();
    howManyIterations /= n;
    int squarePoints[n];
    int circlePoints[n];

    auto start = omp_get_wtime();
#pragma omp parallel
    {
        int threadSquarePoints = 0;
        int threadCirclePoints = 0;

        auto k = omp_get_thread_num();
        std::mt19937 rng(clock() + k);    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_real_distribution<> distribution(-1, 1); // guaranteed unbiased

        for (int i = 0; i < howManyIterations; i++) {
            auto x = distribution(rng);
            auto y = distribution(rng);

            if (x * x + y * y < a)
                threadCirclePoints++;
            threadSquarePoints++;
        }
        squarePoints[k] = threadSquarePoints;
        circlePoints[k] = threadCirclePoints;
    }
    double squarePointsSum = 0;
    for (auto threadSquarePoints : squarePoints)
        squarePointsSum += threadSquarePoints;

    double circlePointsSum = 0;
    for (auto threadCirclePoints : circlePoints)
        circlePointsSum += threadCirclePoints;

    double pi = 4 * a * circlePointsSum / squarePointsSum;
    auto end = omp_get_wtime();

    std::cout << pi << std::endl << "Czas: " << end - start;
    return 0;
}

#pragma clang diagnostic pop