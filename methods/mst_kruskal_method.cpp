/**
 * @file mst_kruskal.cpp
 * @author Aleksey Gladkov
 *
 *
 */

#include "nlohmann/json.hpp"
#include "methods.hpp"
#include <mst_kruskal.hpp>
#include <weighted_graph.hpp>
#include <vector>
#include <iostream>


int graph::MSTKruskalMethod(const nlohmann::json& input, nlohmann::json* output) {
  graph::WeightedGraph<int> graph; // TODO: how to do variable weight type?
  nlohmann::json js;

  for (auto vertex : input["vertices"]) {
    graph.AddVertex(vertex);
    js["vertices"].push_back(vertex);
  }
  for (auto edge : input["edges"]) {
    graph.AddEdge(edge[0], edge[1], edge[2]);
  }

  std::cout << js.dump() << std::endl;

  auto newEdges = MSTKruskal(&graph);
  for ( auto e : newEdges ) {
    js["edges"].push_back({e.first.first, e.first.second, e.second});
  }

  std::cout << js.dump() << std::endl;

  (*output) = {{"MST", js}};

  return 0;
}
