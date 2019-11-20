cmake_minimum_required(VERSION 3.15)
project(FordFulkerson)

set(CMAKE_CXX_STANDARD 17)

add_executable(FordFulkerson main.cpp FordFulkersonList.cpp FordFulkersonList.h FordFulkersonMatrix.cpp FordFulkersonMatrix.h FordFulkersonListv2.cpp FordFulkersonListv2.h)