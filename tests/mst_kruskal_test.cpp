/**
 * @file mst_kruskal_test.cpp
 * @author Aleksey Gladkov
 *
 * 
 */
#include <httplib.h>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>
#include "test_core.hpp"

void TestMSTKruskal(httplib::Client& cli) {
  std::map<std::string, std::pair<nlohmann::json, nlohmann::json>> cases;
  std::vector<std::pair<std::size_t, std::size_t>> empty_list;

  cases["Complex #1"] = {
    {
      {"vertices", {1, 2, 3, 4}},
      {"edges", {{1, 2, 1}, {3, 4, 2}, {2, 4, 5}, {1, 3, 3}}}
    },
    {
      {"MST", {
          {"edges", {{1, 2, 1}, {3, 4, 2}, {1, 3, 3}}},
          {"vertices", {1, 2, 3, 4}}
        }
      }
    }
  };

  for (const auto &[name, value] : cases) {
    std::cout << name << "... ";
    auto output = cli.Post(
      "/MSTKruskal",
      value.first.dump(),
      "application/json"
    );
    std::cout << output->body << std::endl;
    REQUIRE(output->body == value.second.dump());
    REQUIRE_EQUAL(output->body, value.second.dump());
    std::cout << "OK!" << std::endl;
  }
}
