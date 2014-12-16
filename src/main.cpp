
#include <iostream>

#include "Calculator.h"

int main(int argc, char** argv) {
  while (true) {
    std::cout << "> ";
    std::string expression;
    std::cin >> expression;
    std::cout << calc::evaluate_expression(calc::parse_expression(expression)) << std::endl;
  }
  return 0;
}
