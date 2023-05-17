/**
 * @file tests/main.cpp
 * @author Mikhail Lozhnikov
 *
 * Файл с функцией main() для клиентской части программы (набора тестов).
 */

#include <httplib.h>
#include "test.hpp"
#include "test_core.hpp"
#include "weighted_graph.hpp"
#include "mst_kruskal.hpp"
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
  // Порт по-умолчанию.
  int port = 8080;
  // Адрес сервера по-умолчанию.
  std::string host = "127.0.0.1";

  // Обычные тесты на сборку для базовых шаблонов.
  // Сюда ничего добавлять не нужно.
  TestGraph();
  TestOrientedGraph();
  TestWeightedGraph();
  TestWeightedOrientedGraph();

  if (argc >= 2) {
    // Меняем хост, если предоставлен соответствующий аргумент командной строки.
    host = std::string(argv[1]);
  }

  if (argc >= 3) {
    // Меняем порт, если предоставлен соответствующий аргумент командной строки.
    if (std::sscanf(argv[2], "%d", &port) != 1)
      return -1;
  }

  // Адрес подключения в формате хост:порт.
  std::string url = host + ":" + std::to_string(port);

  httplib::Client cli(url.c_str());

  /* Сюда нужно вставить вызов набора тестов для алгоритма. */

  graph::WeightedGraph<int> gr;
  gr.AddVertex(1);
  gr.AddVertex(2);
  gr.AddVertex(3);
  gr.AddVertex(4);
  gr.AddEdge(1, 2, 1);
  gr.AddEdge(2, 3, 2);
  gr.AddEdge(1, 3, 1);
  gr.AddEdge(2, 4, 3);
  gr.AddEdge(1, 4, 3);
  gr.AddEdge(3, 4, 2);

  nlohmann::json js;
  auto MST = MSTKruskal(&gr);
  for ( auto e : MST ) {
    js["edges"].push_back({e.first.first, e.first.second, e.second});
  }
  std::cout << js.dump() << std::endl;

  TestMSTKruskal(cli);
  /* Конец вставки. */

  // Отправляем GET запрос для остановки сервера.
  httplib::Result res = cli.Get("/stop");

  if (res->status != 200)
    return -1;

  return TestSuite::Status();
}
