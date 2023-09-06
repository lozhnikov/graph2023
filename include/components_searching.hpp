/**
 * @file components_searching.hpp
 * @author Dmitrii Pankratov
 *
 * Поиск компонент связности.
 */

 /**
   * @brief Алгоритм поиска компонент связности.
   *
   * @param graph Граф.
   *
   * На вход подаётся ссылка на объект типа graph::Graph, описанный в файле:
   * @sa graph.cpp
   * Алгоритм возвращает список пар: (номер компоненты связности, список id вершин компоненты связности).
  **/

#ifndef INCLUDE_COMPONENTS_SEARCHING_HPP_
#define INCLUDE_COMPONENTS_SEARCHING_HPP_

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <graph.hpp>

size_t comp;

template<class Graph>
void dfs(const Graph& graph,
    std::unordered_map<size_t, bool> *used,
    size_t root,
    std::unordered_map<size_t, std::unordered_set<size_t>>* res) {
    (*used)[root] = true;

    for (size_t way : graph.Edges(root)) {
        if (!(*used)[way]) {
            dfs(graph, used, way, res);
            (*res)[comp].insert(way);
        }
    }
}

template<class Graph>
std::unordered_map <size_t, std::unordered_set<size_t>> ComponentsSearching(const Graph& graph) {
    std::unordered_map<size_t, bool> used;
    std::unordered_map<size_t, std::unordered_set<size_t>> res;

    for (auto vert : graph.Vertices())
        used[vert] = false;

    res.clear();
    comp = 1;

    for (auto vert : graph.Vertices()) {
        if (!used[vert]) {
            dfs(graph, &used, vert, &res);
            res[comp].insert(vert);
            comp++;
        }
    }

    return res;
}

#endif  // INCLUDE_COMPONENTS_SEARCHING_HPP_
