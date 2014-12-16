#include <iostream>
#include <queue>
#include <string>

#include "Calculator.h"

int main(int argc, char** argv) {
  while (true) {
    std::cout << "> ";
    std::string expression;
    std::getline(std::cin, expression);
    std::queue<std::string> parsed_expression = calc::parse_expression(expression);
    std::cout << calc::evaluate_expression(parsed_expression) << std::endl;
  }
  return 0;
}
