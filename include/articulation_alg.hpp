/**
 * @file articulation_alg.hpp
 * @author Vika Kukanova
 *
 * Алгоритм поиска точек сочления..
 */

#ifndef INCLUDE_BRIDGE_SEARCH_HPP_
#define INCLUDE_BRIDGE_SEARCH_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <graph.hpp>

#define Vertex size_t


template<class Graph>
void DFS(const Graph &graph,
         std::unordered_map<size_t, int> *tin,
         std::unordered_map<size_t, int> *low,
         std::unordered_map<size_t, bool> *visited,
         size_t root, size_t dest, int *time,
         std::vector<Vertex> *res) {
  (*visited)[root] = true;
  (*tin)[root] = (*low)[root] = ++(*time);
  int children = 0;
  for (size_t way : graph.Edges(root)) {
    if (way == dest) {
      continue;
    }
    if ((*visited)[way]) {
      (*low)[root] = std::min((*low)[root], (*tin)[way]);
    } else {
      DFS(graph, tin, low, visited, way, root, time, res);
      (*low)[root] = std::min((*low)[root], (*low)[way]);
      if (((*low)[way] >= (*tin)[root]) && (dest != -1)) {
          (*res).push_back(root);
          ++ children;
      }
    }
  }
  if ((dest == -1) && (children > 1))
    (*res).push_back(root);
}

template<class Graph>
std::vector<Vertex> ArticulationAlg(const Graph &graph) {
  /**
   * @brief Алгоритм поиска всех точек сочления в графе за O(N+M).
   *
   * @param graph Граф.
   *
   * На вход подаётся ссылка на объект типа graph::Graph, описанный в файле:
   * @sa graph.cpp
   * Алгоритм возвращает отсортированный список id вершин.
  */
  std::unordered_map<size_t, int> tin;
  std::unordered_map<size_t, int> low;
  std::unordered_map<size_t, bool> visited;
  std::vector<Vertex> res;
  int time = 0;

  auto v = graph.Vertices();

  if (v.begin() != v.end()) {
    DFS(graph, &tin, &low, &visited, *v.begin(), -1, &time, &res);
    std::sort(res.begin(), res.end());
  }

  return res;
}


#endif
