#include <unordered_set>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include "test_core.hpp"
#include <graph.hpp>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <bridge_search.hpp>


using std::unordered_set;
using std::vector;
using std::pair;
using std::make_pair;

using std::out_of_range;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using graph::Graph;

namespace {
/**
 * @brief Класс для хеширования std::pair<size_t, size_t>.
 */
    class Hash {
    public:
        size_t operator()(pair<size_t, size_t> item) const noexcept {
            const size_t prime = 479001599;

            return item.first * prime + item.second;
        }
    };

}  // namespace


void TestBridgeSearch(httplib::Client &cli){
    int num_cases = 1;
    std::vector<std::pair<nlohmann::json, nlohmann::json>> cases(num_cases);
    for(int i = 0; i < num_cases; ++i) {
        cases[i] = {
                {
                        {"vertices", {1, 2, 3}},
                        {"edges", {{1, 2}, {2, 3}}}
                },
                {
                        {"result", {{1, 2}, {2, 3}}}
                }
        };
    }
    for(auto req: cases){
        auto output = cli.Post("/bridge_search", req.first.dump(), "application/json");
        REQUIRE(output->body == req.second.dump());
    }
}