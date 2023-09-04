#include <articulation_alg.hpp>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"
#include <iostream>

using graph::Graph;
void graph::ArticulationAlgMethod(const nlohmann::json &input,
                               nlohmann::json *output) {

  Graph graph;
  for (auto vert : input["vertices"]) {
    graph.AddVertex(vert);
  }
  for (auto edge : input["edges"]) {
    graph.AddEdge(edge[0], edge[1]);
  }
  nlohmann::json result = {
      {"res", ArticulationAlg(graph)},

  };
  (*output) = result;
  std::cout << result;
  return;
}
