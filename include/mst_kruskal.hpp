/**
 * @file mst_kruskal.hpp
 * @author Aleksey Gladkov
 *
 *
 */

#ifndef GRAPH_MST_KRUSKAL_HPP
#define GRAPH_MST_KRUSKAL_HPP


#include "weighted_graph.hpp"
#include <unordered_map>

#include <vector>
#include <unordered_set>

#include <algorithm>


std::size_t find(std::unordered_map<std::size_t, std::size_t>& dsu, std::size_t x);
std::size_t find(std::unordered_map<std::size_t, std::size_t>& dsu, std::size_t x) {
  if (dsu[x] == x) return x;
  return dsu[x] = find(dsu, dsu[x]);
}

void unite(std::unordered_map<std::size_t, std::size_t>& dsu, std::size_t x, std::size_t y) {
  x = find(dsu, x);
  y = find(dsu, y);

  if (std::rand() % 2 == 0)
    dsu[x] = y;
  else
    dsu[y] = x;
}

template<typename Weight>
std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> MSTKruskal(graph::WeightedGraph<Weight>* inputGraph) {
  graph::WeightedGraph<Weight> outputGraph;

  std::unordered_map<std::size_t, std::size_t> dsu;
  for (auto vertex: inputGraph->Vertices())
    dsu.insert({vertex, vertex});


  // create vector with edges
  // like { pair(v1, v2) : weight } or
  // {hash(v1, v2) : weight} hash - symmetric hash function
  std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> edges;
  std::unordered_set<std::size_t> visitedEdges;
  for (auto vertex : inputGraph->Vertices()) {
    for (auto vertex2 : inputGraph->Edges(vertex)) {
      auto tmp1 = vertex;
      auto tmp2 = vertex2;
      if (tmp1 > tmp2)
        std::swap(tmp1, tmp2);
      std::size_t hash = tmp1 * 479001599 + tmp2;

      if (visitedEdges.find(hash) == visitedEdges.end()) {
        visitedEdges.insert(hash);

        edges.push_back(std::make_pair(std::make_pair(tmp1, tmp2), inputGraph->EdgeWeight(tmp1, tmp2)));
      }
    }
  }

  // sort edges by weight
  std::sort(edges.begin(), edges.end(), [](std::pair<std::pair<std::size_t, std::size_t>, std::size_t> a, std::pair<std::pair<std::size_t, std::size_t>, std::size_t> b){
    return a.second < b.second;
  });

  std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::size_t>> newEdges;
  // for each edge in ascent order add his vertices to dsu
  // if vertices are already in one set, skip this edge
  for (auto edge : edges) {
    if (find(dsu, edge.first.first) != find(dsu, edge.first.second)) {
      unite(dsu, edge.first.first, edge.first.second);
      outputGraph.AddVertex(edge.first.first);
      outputGraph.AddVertex(edge.first.second);
      outputGraph.AddEdge(
        edge.first.first,
        edge.first.second,
        inputGraph->EdgeWeight(edge.first.first, edge.first.second)
      );
      newEdges.push_back(
        std::make_pair(
          std::make_pair(
            edge.first.first,
            edge.first.second
          ),
          inputGraph->EdgeWeight(edge.first.first, edge.first.second)
        )
      );
    }
  }

  return newEdges;
}

#endif //GRAPH_MST_KRUSKAL_HPP
