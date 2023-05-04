#include <bridge_search.hpp>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"


using graph::Graph;

void graph::BridgeSearchMethod(const nlohmann::json &input, 
                               nlohmann::json *output) {
  /**
   * @brief Серверная часть алгоритма bridge_search.
   *
   * @param input  Входной JSON.
   * @param output Выходной JSON.
   *
   * Функция Принимает на вход JSON, запускает алгоритм и записывает результат в выходной JSON.
  */
  Graph graph;
  for (auto vert : input["vertices"]) {
    graph.AddVertex(vert);
  }
  for (auto edge : input["edges"]) {
    graph.AddEdge(edge[0], edge[1]);
  }
  (*output) = {{"bridges", BridgeSearch(graph)}};
  return;
}
