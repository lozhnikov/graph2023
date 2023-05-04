/**
 * @file bridge_search.hpp
 * @author Pavel Korniychuk
 *
 * Реализация алгоритма поиска мостов в графе.
 */

#ifndef INCLUDE_BRIDGE_SEARCH_HPP_
#define INCLUDE_BRIDGE_SEARCH_HPP_

#include <algorithm>
#include <map>
#include <vector>
#include <graph.hpp>

#define Edge std::pair<size_t, size_t>


using graph::Graph;

void DFS(const Graph &graph,
         std::map<size_t, int> *tin,
         std::map<size_t, int> *low,
         std::map<size_t, bool> *visited,
         size_t root, size_t dest, int *time,
         std::vector<Edge> *bridges) {
  (*visited)[root] = true;
  (*tin)[root] = (*low)[root] = ++(*time);
  for (size_t way : graph.Edges(root)) {
    if (way == dest) {
      continue;
    }
    if ((*visited)[way]) {
      (*low)[root] = std::min((*low)[root], (*tin)[way]);
    } else {
      DFS(graph, tin, low, visited, way, root, time, bridges);
      (*low)[root] = std::min((*low)[root], (*low)[way]);
      if ((*low)[way] > (*tin)[root]) {
        (*bridges).push_back({way, root});
      }
    }
  }
}

std::vector<Edge> BridgeSearch(const Graph &graph) {
  /**
   * @brief Алгоритм поиска всех мостов в графе.
   *
   * @param graph Граф.
   *
   * На вход подаётся ссылка на объект типа Graph, описанный в файле graph.cpp
   * Алгоритма возвращает отсортированный список рёбер в виде пар:
   * (id одной вершины, id второй вершины) - все мосты графа.
  */
  std::map<size_t, int> tin;
  std::map<size_t, int> low;
  std::map<size_t, bool> visited;
  std::vector<Edge> bridges;
  int time = 0;
  for (auto vert : graph.Vertices()) {
    if (!visited[vert]) {
      DFS(graph, &tin, &low, &visited, vert, -1, &time, &bridges);
    }
  }
  sort(bridges.begin(), bridges.end());
  return bridges;
}

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_
