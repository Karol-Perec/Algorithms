#pragma once

#include <vector>
#include <string>

int computeFlowForAdjacencyListV2(std::vector<std::vector<int>> &adjacencyList,
                                  int startNodeId,
                                  int endNodeId,
                                  int numberOfNodes);

int computeFlowForAdjacencyListV2(std::string fileName);