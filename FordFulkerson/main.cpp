#include <iostream>
#include "FordFulkersonList.h"
#include "FordFulkersonListv2.h"
#include "FordFulkersonMatrix.h"

int main() {
    int maxFlow{};

    std::vector<std::map<int, std::vector<int>>> adjacencyList = {
            {{1, {3, 0}}, {5, {4, 0}}},
            {{2, {5, 0}}, {4, {3, 0}}},
            {{3, {3, 0}}},
            {},
            {{3, {3, 0}}},
            {{4, {6, 0}}}
    };

    std::vector<std::vector<int>> adjacencyListV2 = {
            {0, 1, 3},
            {1, 2, 5},
            {2, 3, 3},
            {1, 4, 3},
            {0, 5, 4},
            {5, 4, 6},
            {4, 3, 3}
    };

    std::vector<std::vector<int>> adjacencyMatrix{
            {0, 3, 0, 0, 0, 4},
            {0, 0, 5, 0, 3, 0},
            {0, 0, 0, 3, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 3, 0, 0},
            {0, 0, 0, 0, 6, 0}
    };

//    maxFlow = computeFlowForAdjacencyMatrix(adjacencyMatrix, 0, 3, 6);
//
//    maxFlow = computeFlowForAdjacencyMatrix("/home/karol/CLionProjects/FordFulkerson/adjacencyMatrix.txt");
//
//    maxFlow = computeFlowForAdjacencyList(adjacencyList, 0, 3, 6);
//
//    maxFlow = computeFlowForAdjacencyList("/home/karol/CLionProjects/FordFulkerson/adjacencyList.txt");
//
//    maxFlow = computeFlowForAdjacencyListV2(adjacencyListV2, 0, 3, 6);
//
//    maxFlow = computeFlowForAdjacencyListV2("/home/karol/CLionProjects/FordFulkerson/adjacencyList.txt");


    std::cout << std::endl << "Max Flow is: " << maxFlow << std::endl;
    return 0;
}