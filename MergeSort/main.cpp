#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include <iostream>
#include <omp.h>

int main() {
    int n = omp_get_max_threads();
    int tabLength = 16;
    int tab[] = {5, 1, 0, 8, 22, 69, 36, 12, 11, 23, 3, 9, 4, 14, 13, 60};
    int dividedThreadTabLength = tabLength/n;

    auto start = omp_get_wtime();
#pragma omp parallel
    {
        auto k = omp_get_thread_num();
        for (auto i =  k*dividedThreadTabLength; i < (k+1)*dividedThreadTabLength; i++) {

        }


    }
    auto end = omp_get_wtime();

    std::cout << "Czas: " << end - start;

    return 0;
}
#pragma clang diagnostic pop