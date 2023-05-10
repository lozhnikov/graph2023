/**
 * @file bridge_search.hpp
 * @author Pavel Korniychuk
 *
 * Реализация алгоритма поиска мостов в графе.
 */

#ifndef INCLUDE_BRIDGE_SEARCH_HPP_
#define INCLUDE_BRIDGE_SEARCH_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <graph.hpp>

#define Edge std::pair<size_t, size_t>


template<class Graph>
void DFS(const Graph &graph,
         std::unordered_map<size_t, int> *tin,
         std::unordered_map<size_t, int> *low,
         std::unordered_map<size_t, bool> *visited,
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
        if (way > root) {
          (*bridges).push_back({root, way});
        } else {
          (*bridges).push_back({way, root});
        }
      }
    }
  }
}

template<class Graph>
std::vector<Edge> BridgeSearch(const Graph &graph) {
  /**
   * @brief Алгоритм поиска всех мостов в графе.
   *
   * @param graph Граф.
   *
   * На вход подаётся ссылка на объект типа graph::Graph, описанный в файле:
   * @sa graph.cpp
   * Алгоритм возвращает отсортированный список рёбер в виде пар:
   * (id одной вершины, id второй вершины) - все мосты графа.
  */
  std::unordered_map<size_t, int> tin;
  std::unordered_map<size_t, int> low;
  std::unordered_map<size_t, bool> visited;
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
