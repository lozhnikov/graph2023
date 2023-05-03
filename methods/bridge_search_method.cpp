#include <nlohmann/json.hpp>
#include "methods.hpp"
#include <graph.hpp>
#include <bridge_search.hpp>

using graph::Graph;


void graph::BridgeSearchMethod(const nlohmann::json& input, nlohmann::json* output){
    Graph graph;
    for(auto vert: input["vertices"]){
        graph.AddVertex(vert);
    }
    for(auto edge: input["edges"]){
        graph.AddEdge(edge[0], edge[1]);
    }
    (*output).push_back({{"result", BridgeSearch(graph)}});
    return;
}