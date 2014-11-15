#include <cctype>
#include <map>
#include <pair>
#include <set>

#include "Calculator.h"

namespace calc {
  std::vector<std::string> tokenize(std::string expression) {
    std::set<std::string> operators{"-","^","+","/","*","(",")"};
    std::vector<std::string> tokens;
    int current_idx = 0;
    while (current_idx < expression.length()) {
      while (isspace(expression[current_idx])) { ++current_idx; }
      int start_idx = current_idx;
      if (isdigit(expression[current_idx])
          || (expression[current_idx] == '-' 
              && (tokens.size()==0 || operators.count(tokens.back()))
              && isdigit(expression[current_idx+1]))) {
        ++current_idx;
        while (isdigit(expression[current_idx])) { ++current_idx; }
      } else {
        ++current_idx;
      }
      tokens.push_back(expression.substr(start_idx, current_idx-start_idx));
    }
    return tokens;
  }
  std::stack<std::string> parse_expression(std::string) {
    std::map<std::string, int> operator_precedence;
    std::stack<std::string> parsed_expression;
    return parsed_expression;
  }
}
