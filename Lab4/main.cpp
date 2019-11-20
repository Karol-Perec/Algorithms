#include <iostream>
#include <omp.h>


int main() {
#pragma omp parallel
    {
        auto n = omp_get_num_threads();
        auto k = omp_get_thread_num();
        std::cout << n << " " << k << std::endl;
    }
    return 0;
}
