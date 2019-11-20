#include "FordFulkersonMatrix.h"
#include <fstream>
#include <algorithm>
#include <queue>
#include <iostream>
#include <climits>

int computeFlowForAdjacencyMatrix(std::vector<std::vector<int>> &adjacencyMatrix, int startNodeId, int endNodeId,
                                  int numberOfNodes) {
    auto inputAdjacencyMatrix{adjacencyMatrix};
    int parent[numberOfNodes];
    std::fill_n(parent, numberOfNodes, -1);
    auto maxFlow = 0;

    while (breadthFirstSearchForAdjacencyMatrix(adjacencyMatrix, startNodeId, endNodeId, numberOfNodes, parent)) {
        int pathFlow = INT_MAX;

        auto pathNodeId = endNodeId;
        while (pathNodeId != startNodeId) {
            pathFlow = std::min(pathFlow, adjacencyMatrix[parent[pathNodeId]][pathNodeId]);
            pathNodeId = parent[pathNodeId];
        }

        maxFlow += pathFlow;

        pathNodeId = endNodeId;
        while (pathNodeId != startNodeId) {
            auto parentPathNodeId = parent[pathNodeId];
            adjacencyMatrix[parentPathNodeId][pathNodeId] -= pathFlow;
            adjacencyMatrix[pathNodeId][parentPathNodeId] += pathFlow;
            pathNodeId = parentPathNodeId;
        }
    }
    printFlowGraphForAdjacencyMatrix(inputAdjacencyMatrix, adjacencyMatrix);
    return maxFlow;
}


int computeFlowForAdjacencyMatrix(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        int startNodeId, endNodeId, numberOfNodes;
        std::vector<std::vector<int>> nodesMatrix;

        file >> startNodeId >> endNodeId >> numberOfNodes;

        for (auto i = 0; i < numberOfNodes; i++) {
            std::vector<int> row;
            int residualFlow;

            for (auto j = 0; j < numberOfNodes; j++) {
                file >> residualFlow;
                row.push_back(residualFlow);
            }

            nodesMatrix.push_back(row);
        }
        return computeFlowForAdjacencyMatrix(nodesMatrix, startNodeId, endNodeId, numberOfNodes);
    }
}

bool breadthFirstSearchForAdjacencyMatrix(const std::vector<std::vector<int>> &adjacencyMatrix,
                                          int startNodeId,
                                          int endNodeId,
                                          int numberOfNodes,
                                          int parent[]) {
    bool visited[numberOfNodes];
    std::fill_n(visited, numberOfNodes, false);
    std::queue<int> queue;
    queue.push(startNodeId);
    visited[startNodeId] = true;

    while (!queue.empty()) {
        auto u = queue.front();
        queue.pop();
        for (auto v = 0; v < numberOfNodes; v++) {
            if (!visited[v] and adjacencyMatrix[u][v] > 0) {
                queue.push(v);
                visited[v] = true;
                parent[v] = u;
                if (v == endNodeId)
                    return visited[endNodeId];
            }
        }
    }

    return visited[endNodeId];
}

void printFlowGraphForAdjacencyMatrix(const std::vector<std::vector<int>> &inputMatrix,
                                      const std::vector<std::vector<int>> &outputMatrix) {
    std::cout << "The flow network for maximum flow is: " << std::endl;
    for (auto i = 0; i < outputMatrix.size(); i++) {
        for (auto j = 0; j < outputMatrix.size(); j++) {
            if (inputMatrix[i][j] != 0)
                std::cout << outputMatrix[j][i] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}
