#include <nlohmann/json.hpp>
#include <graph.hpp>
#include <oriented_graph.hpp>
#include <weighted_graph.hpp>
#include <weighted_oriented_graph.hpp>

using graph::Graph;
using graph::OrientedGraph;
using graph::WeightedGraph;
using graph::WeightedOrientedGraph;

namespace graph {

template<typename GraphType>
int BreadthFirstTraversalMethodHelper(const nlohmann::json& input, nlohmann::json* output);

int BreadthFirstTraversalMethod(const nlohmann::json& input, nlohmann::json* output) {
  std::string graphType = input.at("graph_type");
  
  if (graphType == "Graph")
    return BreadthFirstTraversalMethodHelper<Graph>(input, output);
  else if (graphType == "OrientedGraph")
    return BreadthFirstTraversalMethodHelper<OrientedGraph>(input, output);
  else if (graphType == "WeightedGraph") {
    std::string weightType = input.at("weight_type");
    if (weightType == "int")
      return BreadthFirstTraversalMethodHelper<WeightedGraph<int>>(input, output);
    else
      return -1;
  } else if (graphType == "WeightedOrientedGraph") {
    std::string weightType = input.at("weight_type");
    if (weightType == "int")
      return BreadthFirstTraversalMethodHelper<WeightedOrientedGraph<int>>(input, output);
    else
      return -1;
  }
  
  return -1;
}

template<typename GraphType>
int BreadthFirstTraversalMethodHelper(const nlohmann::json& input, nlohmann::json* output) {
  GraphType graph;
  
  return 0;
}

}  // namespace graph
