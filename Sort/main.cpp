#include <vector>
#include <omp.h>
#include <random>
#include <iostream>

using namespace std;

std::vector<int> merge(const std::vector<int> &leftArray, const std::vector<int> &rightArray, std::vector<int> &array) {
    auto l = 0;
    auto r = 0;

    while (l < leftArray.size() && r < rightArray.size()) {
        if (leftArray[l] <= rightArray[r]) {
            array[l + r] = leftArray[l];
            l++;
        } else {
            array[l + r] = rightArray[r];
            r++;
        }
    }

    while (l < leftArray.size()) {
        array[l + r] = leftArray.at(l);
        l++;
    }

    while (r < rightArray.size()) {
        array[l + r] = rightArray.at(r);
        r++;
    }

    return array;
}

std::vector<int> mergeSort(std::vector<int> &array) {
    if (array.size() == 1) {
        return array;
    } else {
        auto splitPoint = int(array.size() / 2);
        std::vector<int> leftArray(array.begin(), array.begin() + splitPoint);
        std::vector<int> rightArray(array.begin() + splitPoint, array.end());

        return merge(mergeSort(leftArray), mergeSort(rightArray), array);
    }
}

std::vector<int> mergeThreadArrays(const std::vector<std::vector<int>> &arraysToMerge) {
    if (arraysToMerge.size() == 1) {
        return arraysToMerge[0];
    } else {
        std::vector<std::vector<int>> mergedArrays(arraysToMerge.size() / 2);

        omp_set_num_threads(int(arraysToMerge.size() / 2));
#pragma omp parallel shared(arraysToMerge, mergedArrays) default(none)
        {
            const auto threadId = omp_get_thread_num();

            auto leftArray = arraysToMerge[2 * threadId];
            auto rightArray = arraysToMerge[2 * threadId + 1];
            std::vector<int> mergedArray(leftArray.size() + rightArray.size());

            mergedArrays[threadId] = merge(leftArray, rightArray, mergedArray);
        }
        return mergeThreadArrays(mergedArrays);
    }
}

std::vector<int> mergeSortParallel(const std::vector<int> &array) {
    const auto maxThreads = omp_get_max_threads();
    const auto numbersPerThread = int(array.size() / maxThreads);
    std::vector<std::vector<int>> threadArrays(maxThreads);

#pragma omp parallel shared(array, threadArrays) default(none)
    {
        const auto threadId = omp_get_thread_num();
        auto begin = array.begin() + (threadId * numbersPerThread);
        auto end = array.begin() + ((threadId + 1) * numbersPerThread);
        std::vector<int> threadArray(begin, end);

        mergeSort(threadArray);

        threadArrays[threadId] = threadArray;
    }
    return mergeThreadArrays(threadArrays);
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
    const auto size = 100000;
    auto unsortedArray = generateUnsortedArray(size);
    auto unsortedArray2{unsortedArray};

    auto start_time = omp_get_wtime();
    unsortedArray = mergeSortParallel(unsortedArray);
    cout << "  Parallel merge sort TIME: " << omp_get_wtime() - start_time << endl;

    start_time = omp_get_wtime();
    mergeSort(unsortedArray2);
    cout << "Sequential merge sort TIME: " << omp_get_wtime() - start_time << endl;

    return 0;
}