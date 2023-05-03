/**
 * @file methods/main.cpp
 * @author Mikhail Lozhnikov
 *
 * Файл с функией main() для серверной части программы.
 */

#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "methods.hpp"



int main(int argc, char* argv[]) {
  // Порт по-умолчанию.
  int port = 8080;

  if (argc >= 2) {
    // Меняем порт по умолчанию, если предоставлен соответствующий
    // аргумент командной строки.
    if (std::sscanf(argv[1], "%d", &port) != 1)
      return -1;
  }

  std::cerr << "Listening on port " << port << "..." << std::endl;

  httplib::Server svr;

  // Обработчик для GET запроса по адресу /stop. Этот обработчик
  // останавливает сервер.
  svr.Get("/stop", [&](const httplib::Request&, httplib::Response&) {
    // svr.stop();
    std::cout << "close server(tipo)" << "\n\n";
  });

  /* Сюда нужно вставить обработчик post запроса для алгоритма. */

  // svr.Post("/kun_algorithm",
  // [&](const httplib::Request&, httplib::Response&) {
  //   // MyAlgorithmNameMethod(const nlohmann::json& input, nlohmann::json* output);
  //   // svr.stop();
  //   std::cout << "kun_algorithm(tipo)" << "\n\n";
  // });

  svr.Post("/kun_algorithm", [&](const httplib::Request& req, httplib::Response& res) {
      std::cout << "req.body = " << req.body << "\n";
      const nlohmann::json input = nlohmann::json::parse(req.body);
      nlohmann::json* output = new nlohmann::json();
      graph::KunAlgorithmMethod(input, output);
      std::cout << "result: " << (*output).dump() << "\n";
      res.set_content((*output).dump(), "application/json");
  });

  /* Конец вставки. */

  // Эта функция запускает сервер на указанном порту. Программа не завершится
  // до тех пор, пока сервер не будет остановлен.
  svr.listen("0.0.0.0", port);

  return 0;
}
