#pragma once

#include <vector>
#include <string>
#include <map>

int computeFlowForAdjacencyList(std::vector<std::map<int, std::vector<int>>> &adjacencyList,
                                int startNodeId,
                                int endNodeId,
                                int numberOfNodes);

int computeFlowForAdjacencyList(std::string fileName);

bool breadthFirstSearchForAdjacencyList(const std::vector<std::map<int, std::vector<int>>> &adjacencyList,
                                        int startNodeId,
                                        int endNodeId,
                                        int numberOfNodes,
                                        int parent[]);

void printFlowGraphForAdjacencyList(const std::vector<std::map<int, std::vector<int>>> &adjacencyList);