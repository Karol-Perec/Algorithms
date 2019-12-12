#pragma once

#include <vector>
#include <string>
#include <map>

int computeFlowForAdjacencyList(std::vector<std::map<int, int>> &adjacencyList,
                                int startNodeId,
                                int endNodeId,
                                int numberOfNodes);

int computeFlowForAdjacencyList(std::string fileName);

bool breadthFirstSearchForAdjacencyList(const std::vector<std::map<int, int>> &adjacencyList,
                                        int startNodeId,
                                        int endNodeId,
                                        int numberOfNodes,
                                        int parent[]);

void insertBackwardsEdges(std::vector<std::map<int, int>> &adjacencyList);

void printFlowGraphForAdjacencyList(const std::vector<std::map<int, int>> &inputAdjacencyList,
                                    const std::vector<std::map<int, int>> &outputAdjacencyList);
