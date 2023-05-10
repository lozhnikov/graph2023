#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <graph.hpp>

using graph::Graph;

bool TryKuhn(size_t v, std::unordered_map<size_t, int> *mt,
             std::unordered_map<size_t, bool> *used, const Graph &graph) {
  if ((*used)[v]) {
    return false;
  }
  (*used)[v] = true;
  for (size_t to : graph.Edges(v)) {
    if ((*mt)[to] == -1 || TryKuhn((*mt)[to], mt, used, graph)) {
      (*mt)[to] = v;
      return true;
    }
  }
  return false;
}

std::vector<std::pair<size_t, size_t>>
KunAlgorithm(const Graph &graph, const std::vector<size_t> &vertices_first_part,
             const std::vector<size_t> &vertices_second_part) {
  std::unordered_map<size_t, bool> used;
  std::unordered_map<size_t, int> mt;

  for (auto vert : graph.Vertices()) {
    used[vert] = false;
    mt[vert] = -1;
  }

  for (auto v : vertices_first_part) {
    for (auto vert : graph.Vertices()) {
      used[vert] = false;
    }
    TryKuhn(v, &mt, &used, graph);
  }
  std::vector<std::pair<size_t, size_t>> result;
  for (auto item : mt) {
    if (item.second != -1) {
      result.push_back({item.first, item.second});
    }
  }
  return result;
}
