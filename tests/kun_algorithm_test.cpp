#include <kun_algorithm.hpp>
#include <httplib.h>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "test_core.hpp"

using graph::Graph;

void TestKunAlgorithmSimple(httplib::Client *cli) {
  int num_cases = 1;
  std::vector<std::pair<nlohmann::json, nlohmann::json>> cases(num_cases);
  nlohmann::json input = {{"vertices", {1, 2, 3, 4, 5}},
                          {"edges", {{1, 2}, {2, 3}, {3, 4}, {4, 5}}},
                          {"vertices_first_part", {1, 3, 5}},
                          {"vertices_second_part", {2, 4}}};
  nlohmann::json expected = {
      {"result", {{2, 1}, {4, 3}}},
  };

  auto output = cli->Post("/kun_algorithm", input.dump(), "application/json");
  REQUIRE(output->body == expected.dump());
  REQUIRE_EQUAL(output->body, expected.dump());
}

void TestKunAlgorithm(httplib::Client *cli) {
  TestSuite suite("TestKunAlgorithm");
  RUN_TEST_REMOTE(suite, cli, TestKunAlgorithmSimple);
}
