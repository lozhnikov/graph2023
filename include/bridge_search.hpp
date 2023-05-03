#pragma once
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <graph.hpp>
#define Edge std::pair<size_t, size_t>

using graph::Graph;

void DFS(Graph &graph,
         std::vector<int> &tin, std::vector<int> &low,
         std::vector<bool> &visited,
         int root, int dest,
         int &time, std::vector<Edge> &bridges) {
    visited[root] = true;
    tin[root] = low[root] = ++time;
    for (size_t way: graph.Edges(root)) {
        if (way == dest) {
            continue;
        }
        if (visited[way]) {
            low[root] = std::min(low[root], tin[way]);
        } else {
            DFS(graph, tin, low, visited, way, root, time, bridges);
            low[root] = std::min(low[root], low[way]);
            if (low[way] > tin[root]) {
                bridges.push_back({way, root});
            }
        }
    }
}

std::vector<Edge> BridgeSearch(Graph &graph) {
    std::cout << "START BridgeSearch" << "\n";
    std::size_t vertices_num = graph.NumVertices();
    std::vector<int> tin(vertices_num);
    std::vector<int> low(vertices_num);
    std::vector<bool> visited(vertices_num);
    std::vector<Edge> bridges;
    int time = 0;
    for (auto vert: graph.Vertices()) {
        if (!visited[vert]) {
            DFS(graph, tin, low, visited, vert, -1, time, bridges);
        }
    }
    return bridges;
}