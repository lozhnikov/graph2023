#include <kun_algorithm.hpp>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"

using graph::Graph;

void graph::KunAlgorithmMethod(const nlohmann::json &input,
                               nlohmann::json *output) {
  Graph graph;
  for (auto vert : input["vertices"]) {
    graph.AddVertex(vert);
  }
  for (auto edge : input["edges"]) {
    graph.AddEdge(edge[0], edge[1]);
  }
  nlohmann::json result = {
      {"result", KunAlgorithm(graph, input["vertices_first_part"],
                              input["vertices_second_part"])},
  };
  (*output) = result;
  return;
}
