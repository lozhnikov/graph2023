#include <nlohmann/json.hpp>
#include "methods.hpp"
#include <graph.hpp>
#include <kun_algorithm.hpp>


using graph::Graph;

void graph::KunAlgorithmMethod(const nlohmann::json& input, nlohmann::json* output) {
    Graph graph;
    for(auto vert: input["vertices"]){
        graph.AddVertex(vert);
    }
    for(auto edge: input["edges"]){
        graph.AddEdge(edge[0], edge[1]);
    }
    std::cout << "KunAlgorithmMethod add result" << "\n";
    nlohmann::json result = {
        {"result", KunAlgorithm(graph, input["vertices_first_part"], input["vertices_second_part"])},
    };
    (*output) = result;
    std::cout << "KunAlgorithmMethod DONE" << "\n";
    return;
}