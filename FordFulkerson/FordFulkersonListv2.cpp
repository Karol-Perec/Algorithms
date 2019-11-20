#include "FordFulkersonListv2.h"
#include "FordFulkersonMatrix.h"
#include <fstream>
#include <queue>
#include <iostream>

int computeFlowForAdjacencyListV2(std::vector<std::vector<int>> &adjacencyList, int startNodeId, int endNodeId,
                                  int numberOfNodes) {
    std::vector<std::vector<int>> adjacencyMatrix(numberOfNodes, std::vector<int>(numberOfNodes, 0));
    for (auto edge : adjacencyList)
        adjacencyMatrix[edge[0]][edge[1]] = edge[2];

    return computeFlowForAdjacencyMatrix(adjacencyMatrix, startNodeId, endNodeId, numberOfNodes);
}


int computeFlowForAdjacencyListV2(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        int startNodeId, endNodeId, numberOfNodes;
        file >> startNodeId >> endNodeId >> numberOfNodes;
        std::vector<std::vector<int>> adjacencyMatrix(numberOfNodes, std::vector<int>(numberOfNodes, 0));

        while (!file.eof()) {
            int u, v, residualFlow;
            file >> u >> v >> residualFlow;

            adjacencyMatrix[u][v] = residualFlow;
        }
        return computeFlowForAdjacencyMatrix(adjacencyMatrix, startNodeId, endNodeId, numberOfNodes);
    }
}
