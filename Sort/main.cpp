#include <algorithm>
#include <vector>
#include <omp.h>
#include <random>
#include <iostream>
#include <functional>

using namespace std;

std::vector<int> merge(const std::vector<int> &left, const std::vector<int> &right, std::vector<int> &original) {
    int l = 0;
    int r = 0;

    //wykonujemy petle while dopoki vektory do złaczenia nie beda puste
    //porownujemy i wpisujemy w odpowiednie miejsce
    while (l < left.size() && r < right.size()) {
        if (left.at(l) <= right.at(r)) {
            original.at(l + r) = left.at(l);
            l++;
        } else {
            original.at(l + r) = right.at(r);
            r++;
        }
    }

    //jezeli pozostaly niedopasowane to jest wpisuje na koniec
    for (; l < left.size(); l++) {
        original.at(l + r) = left.at(l);
    }

    for (; r < right.size(); r++) {
        original.at(l + r) = right.at(r);
    }

    return original;
}

std::vector<int> mergeSort(std::vector<int> &array) {
    if (array.size() < 2) {
        return array;
    } else {
        auto middle = int(array.size() / 2);
        std::vector<int> left(array.begin(), array.begin() + middle);
        std::vector<int> right(array.begin() + middle, array.end());
        return merge(mergeSort(left), mergeSort(right), array);
    }
}

std::vector<int> mergeParallel(const std::vector<std::vector<int>> &vectors) {
    //sprawdza ile wektorów, jak jeden to nie ma co mergowac
    if (vectors.size() < 2) {
        return vectors.at(0);
    } else {
        std::vector<std::vector<int>> reduced(vectors.size() / 2);

#pragma omp parallel shared(vectors, reduced) default(none)
        {
            int current_thread = omp_get_thread_num();
            try {
                std::vector<int> a = vectors.at(current_thread * 2);
                std::vector<int> b = vectors.at(current_thread * 2 + 1);
                std::vector<int> placeholder(a.size() + b.size());
                reduced.at(current_thread) = merge(a, b, placeholder);
            } catch (const std::out_of_range &e) {}
        }

        return mergeParallel(reduced);
    }
}

std::vector<int> mergeSortParallel(std::vector<int> &array) {
    const auto element_for_thread = int(array.size() / omp_get_max_threads());
    std::vector<std::vector<int>> sub_problem(omp_get_max_threads());

#pragma omp parallel shared(array, sub_problem) default(none)
    {
        int current_thread = omp_get_thread_num();
        auto start = array.begin() + (current_thread * element_for_thread);
        auto stop = array.begin() + ((current_thread + 1) * element_for_thread);

        std::vector<int> sub_array(start, stop);
        mergeSort(sub_array);

        sub_problem.at(current_thread) = sub_array;
    }

    return mergeParallel(sub_problem);
}

std::vector<int> generateUnsortedArray(int size) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(INT_MIN, INT_MAX);

    std::vector<int> unsortedArray(size);
    for (auto &i : unsortedArray)
        i = dist(rng);

    return unsortedArray;
}

int main() {
    const auto size = 10000;
    auto unsortedArray = generateUnsortedArray(size);
    auto unsortedArray2{unsortedArray};

    auto start_time = omp_get_wtime();
    unsortedArray = mergeSortParallel(unsortedArray);
    cout << "Parallel merge sort TIME: " << omp_get_wtime() - start_time << endl;

    start_time = omp_get_wtime();
    mergeSort(unsortedArray2);
    cout << "Sequential merge sort TIME: " << omp_get_wtime() - start_time << endl;

    return 0;
}