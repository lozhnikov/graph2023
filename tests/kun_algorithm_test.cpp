#include <kun_algorithm.hpp>
#include <httplib.h>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>
#include <graph.hpp>
#include <nlohmann/json.hpp>
#include "test_core.hpp"

using graph::Graph;

void TestKunAlgorithmSimple(httplib::Client *cli) {
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

std::vector<int> GenRandomArray(std::mt19937 *gen, size_t count, int from,
                                int to) {
  std::uniform_int_distribution<int> dist(from, to);
  std::vector<int> data(count);
  for (int &cur : data) {
    cur = dist(*gen);
  }
  return data;
}

std::vector<std::vector<int>> GenRandomEdges(std::mt19937 *gen, int count,
                                             int to) {
  std::uniform_int_distribution<int> dist(count, count + to - 1);
  std::vector<std::vector<int>> data;
  std::set<int> memory;
  bool value_in_memory;
  int value;
  for (int i = 0; i < count; ++i) {
    // data[i][0] = i;

    if (memory.size() == to) {
      memory.clear();
    }

    do {
      value = dist(*gen);
      value_in_memory = memory.find(value) != memory.end();
    } while (value_in_memory);

    memory.insert(value);
    // data[i][1] = value;
    data.push_back({i, value});
  }
  return data;
}

void TestKunAlgorithmRandom(httplib::Client *cli) {
  int left_size = 10;
  int right_size = 5;
  std::random_device rd;
  std::mt19937 generator(rd());

  std::vector<int> vertices(left_size + right_size);
  std::vector<int> vertices_first_part;
  std::vector<int> vertices_second_part;
  for (int i = 0; i < left_size + right_size; ++i) {
    vertices[i] = i;
    if (i < left_size) {
      vertices_first_part.push_back(i);
    } else {
      vertices_second_part.push_back(i);
    }
  }

  std::vector<std::vector<int>> edges =
      GenRandomEdges(&generator, left_size, right_size);

  nlohmann::json input = {{"vertices", vertices},
                          {"edges", edges},
                          {"vertices_first_part", vertices_first_part},
                          {"vertices_second_part", vertices_second_part}};
  nlohmann::json expected = {
      {"result", {{2, 1}, {4, 3}}},
  };

  auto output = cli->Post("/kun_algorithm", input.dump(), "application/json");
  nlohmann::json result = nlohmann::json::parse(output->body);
  std::cout << result.dump() << "\n";
  std::set<int> left;
  std::set<int> right;
  for (std::vector<int> pair : result["result"]) {
    left.insert(pair[0]);
    right.insert(pair[1]);
  }

  REQUIRE(left.size() == right.size());
}

void TestKunAlgorithm(httplib::Client *cli) {
  TestSuite suite("TestKunAlgorithm");
  RUN_TEST_REMOTE(suite, cli, TestKunAlgorithmSimple);
  RUN_TEST_REMOTE(suite, cli, TestKunAlgorithmRandom);
}
