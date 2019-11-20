#include "FordFulkersonList.h"
#include <fstream>
#include <algorithm>
#include <queue>
#include <iostream>
#include <climits>

int computeFlowForAdjacencyList(std::vector<std::map<int, std::vector<int>>> &adjacencyList,
                                int startNodeId,
                                int endNodeId,
                                int numberOfNodes) {
    int parent[numberOfNodes];
    std::fill_n(parent, numberOfNodes, -1);
    auto maxFlow = 0;

    while (breadthFirstSearchForAdjacencyList(adjacencyList, startNodeId, endNodeId, numberOfNodes, parent)) {
        int pathFlow = INT_MAX;

        auto pathNodeId = endNodeId;
        while (pathNodeId != startNodeId) {
            pathFlow = std::min(pathFlow, adjacencyList[parent[pathNodeId]][pathNodeId][0]);
            pathNodeId = parent[pathNodeId];
        }

        maxFlow += pathFlow;

        pathNodeId = endNodeId;
        while (pathNodeId != startNodeId) {
            auto parentPathNodeId = parent[pathNodeId];
            adjacencyList[parentPathNodeId][pathNodeId][0] -= pathFlow;
            adjacencyList[parentPathNodeId][pathNodeId][1] += pathFlow;
            pathNodeId = parentPathNodeId;
        }
    }
    printFlowGraphForAdjacencyList(adjacencyList);
    return maxFlow;
}

int computeFlowForAdjacencyList(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Can open file";
        exit(-1);
    } else {
        int startNodeId, endNodeId, numberOfNodes;
        file >> startNodeId >> endNodeId >> numberOfNodes;
        std::vector<std::map<int, std::vector<int>>> edgesList(numberOfNodes);

        while (!file.eof()) {
            int u, v, residualFlow;
            file >> u >> v >> residualFlow;

            edgesList[u].insert(std::pair<int, std::vector<int>>(v, {residualFlow, 0}));
        }
        return computeFlowForAdjacencyList(edgesList, startNodeId, endNodeId, numberOfNodes);
    }
}

bool breadthFirstSearchForAdjacencyList(const std::vector<std::map<int, std::vector<int>>> &adjacencyList,
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
        for (auto adjacentNode : adjacencyList[u]) {
            if (!visited[adjacentNode.first] and adjacentNode.second[0] > 0) {
                queue.push(adjacentNode.first);
                visited[adjacentNode.first] = true;
                parent[adjacentNode.first] = u;
                if (adjacentNode.first == endNodeId)
                    return visited[endNodeId];
            }
        }
    }

    return visited[endNodeId];
}

void printFlowGraphForAdjacencyList(const std::vector<std::map<int, std::vector<int>>> &adjacencyList) {
    std::cout << "The flow network for maximum flow is: " << std::endl;
    for (auto u = 0; u < adjacencyList.size(); u++) {
        for (auto adjacentNodes : adjacencyList[u]) {
            std::cout << u << "--(" << adjacentNodes.second[1] << ")-->" << adjacentNodes.first << std::endl;
        }
    }
}