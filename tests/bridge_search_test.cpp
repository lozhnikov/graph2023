#include <algorithm>
#include <random>
#include <vector>
#include <httplib.h>
#include <graph.hpp>
#include <nlohmann/json.hpp>
#include "test_core.hpp"

using graph::Graph;


void TestBridgeSearch(httplib::Client *cli) {
  /**
   * @brief Тесты алгоритма bridge_search.
   *
   * @param cli Клиент, отправляющий запросы.
   *
   * Функция тестирует алгоритм, Отправляя JSON-ы с клиента, и 
   * проверяя выходные JSON-ы на корректность.
  */
  std::map<std::string, std::pair<nlohmann::json, nlohmann::json>> cases;
  std::vector<std::pair<size_t, size_t>> empty_list;
  cases["Empty"] = {
    {
      {"vertices", empty_list},
      {"edges", empty_list}
    },
    {
      {"bridges", empty_list}
    }
  };
  cases["One line"] = {
    {
      {"vertices", {1, 2, 3, 10}},
      {"edges", {{1, 2}, {2, 3}, {3, 10}}}
    },
    {
      {"bridges", {{1, 2}, {2, 3}, {3, 10}}}
    }
  };
  cases["No edges"] = {
    {
      {"vertices", {1, 2, 3, 4}},
      {"edges", empty_list}
    },
    {
      {"bridges", empty_list}
    }
  };
  cases["All connected"] = {
    {
      {"vertices", {1, 2, 3}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}}}
    },
    {
      {"bridges", empty_list}
    }
  };
  cases["Multiple Connectivity components"] = {
    {
      {"vertices", {1, 2, 3, 4, 5}},
      {"edges", {{1, 2}, {3, 4}}}
    },
    {
      {"bridges", {{1, 2}, {3, 4}}}
    }
  };
  cases["Complex case"] = {
    {
      {"vertices", {1, 2, 3, 4, 5, 6, 7, 8}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 6}, {6, 7}}}
    },
    {
      {"bridges", {{3, 4}, {4, 6}, {6, 7}}}
    }
  };
  for (const auto &[name, value] : cases) {
    auto output = cli->Post("/bridge_search",
                            value.first.dump(), "application/json");
    REQUIRE(output->body == value.second.dump());
  }

  // Random test
  int vertices_num = 60;
  int edges_num = 30;

  std::vector<size_t> vertices(vertices_num);
  std::iota(vertices.begin(), vertices.end(), 0);

  std::vector<std::pair<size_t, size_t>> edges;
  std::mt19937 generator(345);
  std::uniform_int_distribution dist(0, vertices_num-1);
  for (int i = 0; i < edges_num; ++i) {
    size_t vert1 = dist(generator);
    size_t vert2 = dist(generator);
    if (vert1 > vert2) {
      std::swap(vert1, vert2);
    }
    edges.push_back({vert1, vert2});
  }
  sort(edges.begin(), edges.end());
  edges.erase(unique(edges.begin(), edges.end()), edges.end());
  nlohmann::json random_graph = {
      {"vertices", vertices},
      {"edges", edges}
  };
  auto output = cli->Post("/bridge_search",
                          random_graph.dump(), "application/json");
}
