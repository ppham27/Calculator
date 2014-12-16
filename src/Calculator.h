#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <queue>
#include <string>
#include <vector>

namespace calc {
  std::vector<std::string> tokenize(std::string expression);
  std::queue<std::string> parse_expression(std::string);
  double evaluate_expression(std::queue<std::string> expression);
}

#endif
