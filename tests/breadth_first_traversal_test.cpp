/**
 * @file breadth_first_traversal_test.cpp
 * @author Mikhail Lozhnikov
 *
 * Тесты для алгоритма graph::BreadthFirstTraversal.
 */

#include "test_core.hpp"
#include <httplib.h>

static void SimpleTest(httplib::Client* cli);

void TestBreadthFirstTraversal(httplib::Client* cli) {
  TestSuite suite("TestBreadthFirstTraversal");

  RUN_TEST_REMOTE(suite, cli, SimpleTest);
}

static void SimpleTest(httplib::Client* cli) {
}

