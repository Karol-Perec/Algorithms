#pragma once

#include <vector>
#include <string>

int computeFlowForAdjacencyMatrix(std::vector<std::vector<int>> &adjacencyMatrix,
                                  int startNodeId,
                                  int endNodeId,
                                  int numberOfNodes);

int computeFlowForAdjacencyMatrix(std::string fileName);

bool breadthFirstSearchForAdjacencyMatrix(const std::vector<std::vector<int>> &adjacencyMatrix,
                                          int startNodeId,
                                          int endNodeId,
                                          int numberOfNodes,
                                          int parent[]);

void printFlowGraphForAdjacencyMatrix(const std::vector<std::vector<int>> &inputMatrix,
                                      const std::vector<std::vector<int>> &outputMatrix);