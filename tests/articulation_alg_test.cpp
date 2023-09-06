#include <articulation_alg.hpp>
#include <httplib.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <graph.hpp>
#include <nlohmann/json.hpp>
#include "test_core.hpp"

using graph::Graph;

void Function(const Graph& graph,
              size_t root,
              std::unordered_map<long unsigned int, bool>* used) {
    (*used)[root] = true;

    for (size_t way : graph.Edges(root)) {
        if (!(*used)[way]) {
            Function(graph, way, used);
        }
    }
}

void TestArticulationAlgCore(httplib::Client *cli) {
  /**
   * @brief Тесты алгоритма articulation_alg.
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
      {"res", empty_list}
    }
  };
  cases["One line"] = {
    {
      {"vertices", {1, 2, 3, 10}},
      {"edges", {{1, 2}, {2, 3}, {3, 10}}}
    },
    {
      {"res", {2, 3}}
    }
  };
  cases["No edges"] = {
    {
      {"vertices", {1, 2, 3, 4}},
      {"edges", empty_list}
    },
    {
      {"res", empty_list}
    }
  };
  cases["All connected"] = {
    {
      {"vertices", {1, 2, 3}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}}}
    },
    {
      {"res", empty_list}
    }
  };
  cases["Multiple Connectivity components"] = {
    {
      {"vertices", {1, 2, 3, 4, 5}},
      {"edges", {{1, 2}, {4, 3}}}
    },
    {
      {"res", empty_list}
    }
  };
  cases["Complex case"] = {
    {
      {"vertices", {1, 2, 3, 4, 5, 6, 7}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 6}, {6, 7}}}
    },
    {
      {"res", {3, 4, 6}}
    }
  };
  for (const auto &[name, value] : cases) {
    std::cout << name << "... ";
    auto output = cli->Post("/ArticulationAlg",
                            value.first.dump(), "application/json");

    REQUIRE(output->body == value.second.dump());
    REQUIRE_EQUAL(output->body, value.second.dump());
    std::cout << "OK!\n";
  }

    std::cout << "Random test... ";
  int vertices_num = 100;
  int edges_num = 150;


  size_t n = rand() % 10 + 1;
  graph::Graph graph;
  graph:: Graph graph2;
  std::vector<size_t> res;
  int size = 0;
  int tmp = 0;
  size_t root;
  std::unordered_map <long unsigned int, bool> used;

  std::vector<size_t> vertices(n);
  for (int i = 1; i <= n; i++) {
    vertices[i-1] = i;
  }
  std::vector<std::pair<size_t, size_t>> edges;

  for (int i = 1; i < n-1; i++) {
    edges.push_back({i, i+1});
  }

  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      size_t k = rand() % 2;
        if (k == 1) {
          edges.push_back({i, j});
        }
    }
  }

  nlohmann::json random_graph = {
      {"vertices", vertices},
      {"edges", edges}
  };
  auto output = cli->Post("/ArticulationAlg",
                          random_graph.dump(), "application/json");
  auto json_res = nlohmann::json::parse(output->body);
  for (auto vert: json_res["res"]) {
    res.push_back(vert);
  }

  for (auto vert : vertices) {
    graph.AddVertex(vert);
  }
  for (auto edge : edges) {
    graph.AddEdge(edge.first, edge.second);
  }

  for (auto vert : graph.Vertices())
        used[vert] = false;
  graph2 = graph;
  size = res.size();
  for (int i = 1; i <= size; i++) {
    graph2.RemoveVertex(res[i]);
    if (i == 1)
        root = res[2];
    if (i != 1)
        root = res[1];

    Function(graph2, root, &used);
    int k = 0;
    for (int j = 0; j <= n; j++) {
        if (used[res[j]] == false) {
            k = 1;
        }
    }
    tmp += k;
  }
  REQUIRE_EQUAL(tmp, size);
  std::cout << "OK!\n";

}

void TestArticulationAlg(httplib::Client *cli) {
    TestSuite suite("TestArticulationAlg");
    RUN_TEST_REMOTE(suite, cli, TestArticulationAlgCore);
}
