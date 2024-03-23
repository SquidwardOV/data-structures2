
Solution.h
//---------------------------------------------------------------------------------------------------------------------------  
#pragma once
#include <vector>

class Solution {
public:
    void findPath(std::vector<std::vector<int>>& graph, int node, std::vector<int>& path, std::vector<std::vector<int>>& result);

    std::vector<std::vector<int>> allPaths(std::vector<std::vector<int>>& graph);
};


//----------------------------------------------------------------------------------------------------------------------
Solution.cpp
//----------------------------------------------------------------------------------------------------------------------
  #include "solution.h"

void Solution::findPath(std::vector<std::vector<int>>& graph, int node, std::vector<int>& path, std::vector<std::vector<int>>& result) {
    path.push_back(node);

    if (node == graph.size() - 1) {
        result.push_back(path);
    }
    else {
        for (int nextNode : graph[node]) {
            findPath(graph, nextNode, path, result);
        }
    }

    path.pop_back();
}

std::vector<std::vector<int>> Solution::allPaths(std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    findPath(graph, 0, path, result);
    return result;
}
//----------------------------------------------------------------------------------------------------------------------
main.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include "solution.h"

int main() {
    std::vector<std::vector<int>> graph = { {1, 2}, {3}, {3}, {} };

    Solution solution;
    std::vector<std::vector<int>> paths = solution.allPaths(graph);

    for (std::vector<int> path : paths) {
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
