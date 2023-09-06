#include <components_searching.hpp>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"
#include <iostream>

using graph::Graph;

void graph::ComponentsSearchingMethod(const nlohmann::json& input,
    nlohmann::json* output) {
    Graph graph;

    for (auto vert : input["vertices"]) {
        graph.AddVertex(vert);
    }

    for (auto edge : input["edges"]) {
        graph.AddEdge(edge[0], edge[1]);
    }

    (*output) = { {"components", ComponentsSearching(graph)} };
    return;
}
