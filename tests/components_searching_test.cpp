#include <components_searching.hpp>
#include <httplib.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <graph.hpp>
#include <nlohmann/json.hpp>
#include "test_core.hpp"

using graph::Graph;


void TestComponentsSearchingCore(httplib::Client *cli) {
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
      {"components", empty_list}
    }
  };
  cases["One line"] = {
    {
      {"vertices", {1, 2, 3, 10}},
      {"edges", {{1, 2}, {2, 3}, {3, 10}}}
    },
    {
      {"components", {{1,{10,3,2,1}}}}
    }
  };
  cases["No edges"] = {
    {
      {"vertices", {1, 2, 3, 4}},
      {"edges", empty_list}
    },
    {
      {"components", {{4,{1}},{3,{2}},{2,{3}},{1,{4}}}}
    }
  };
  cases["All connected"] = {
    {
      {"vertices", {1, 2, 3}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}}}
    },
    {
      {"components", {{1, {3, 1, 2}}}}
    }
  };
  cases["Multiple Connectivity components"] = {
    {
      {"vertices", {1, 2, 3, 4, 5}},
      {"edges", {{1, 2}, {4, 3}}}
    },
    {
      {"components", {{3,{2,1}},{2,{4,3}},{1,{5}}}}
    }
  };
  cases["Complex case"] = {
    {
      {"vertices", {1, 2, 3, 4, 5, 6, 7}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 6}, {6, 7}}}
    },
    {
      {"components", {{2,{5}},{1,{7,6,4,3,1,2}}}}
    }
  };
  for (const auto &[name, value] : cases) {
    std::cout << name << "... ";
    auto output = cli->Post("/ComponentsSearching",
                            value.first.dump(), "application/json");
    REQUIRE(output->body == value.second.dump());
    REQUIRE_EQUAL(output->body, value.second.dump());
    std::cout << "OK!\n";
  }

    std::cout << "Random test... ";
    int vertices_num = 100;
    int edges_num = 150;
    int n = rand() % 30 + 1;

    graph::Graph graph;

    std::vector<size_t> vertices(n);
    for (int i = 1; i <= n; i++) {
    vertices[i-1] = i;
    }

    std::vector<std::pair<size_t, size_t>> edges;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int k = rand() % 2;
            if (k == 1)
                edges.push_back({i, j});
        }
    }

    std::unordered_map <size_t, std::unordered_set<size_t>> result;
    result.clear();
    size_t testvert = 0;

    nlohmann::json random_graph = {
      {"vertices", vertices},
      {"edges", edges}
    };

    auto output = cli->Post("/ComponentsSearching",
                          random_graph.dump(), "application/json");
    auto json_res = nlohmann::json::parse(output->body);

    int k = 1;

    for (auto vert: json_res["components"]) {
        for (auto ver: vert){
            if (ver == k) {
                k++;
            }
            else {
                for (auto ve: ver) {
                    testvert++;
                }
            }
        }
  }

    REQUIRE_EQUAL(testvert, n);
    std::cout << "OK!\n";

}

void TestComponentsSearching(httplib::Client *cli) {
    TestSuite suite("TestComponentsSearching");
    RUN_TEST_REMOTE(suite, cli, TestComponentsSearchingCore);
}
