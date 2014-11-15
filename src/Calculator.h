#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stack>
#include <string>
#include <vector>

namespace calc {
  std::vector<std::string> tokenize(std::string expression);
  std::stack<std::string> parse_expression(std::string);
}

#endif
