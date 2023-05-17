#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"
#include <matching_edmonds.hpp>

using graph::Graph;

void graph::MatchingEdmondsMethod(const nlohmann::json &input,
                               nlohmann::json *output) {
  /**
   * 
   * @brief Серверная часть алгоритма matching_edmonds.
   * @sa ../include/matching_edmonds
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
  (*output) = {{"greatest matching", MatchingEdmonds(graph)}};
  return;
}
