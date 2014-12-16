#include <cmath>
#include <cctype>
#include <map>
#include <queue>
#include <set>
#include <stack>

#include "Calculator.h"

namespace calc {
  std::vector<std::string> tokenize(std::string expression) {
    std::set<std::string> operators{"-","^","+","/","*","(",")"};
    std::vector<std::string> tokens;
    int current_idx = 0;
    while (current_idx < expression.length()) {
      while (isspace(expression[current_idx])) { ++current_idx; }
      int start_idx = current_idx;
      if (isdigit(expression[current_idx]) || expression[current_idx] == '.'
          || (expression[current_idx] == '-' 
              && (tokens.size()==0 || operators.count(tokens.back()))
              && isdigit(expression[current_idx+1]))) {
        ++current_idx;
        while (isdigit(expression[current_idx]) || expression[current_idx] == '.') { ++current_idx; }
      } else {
        ++current_idx;
      }
      tokens.push_back(expression.substr(start_idx, current_idx-start_idx));
    }
    return tokens;
  }
  
  std::queue<std::string> parse_expression(std::string expression) {    
    // higher precedence is better
    // true means right associativity
    std::map<std::string, std::pair<int, bool>> operator_precedence;
    operator_precedence["-"] = std::make_pair(2, false);
    operator_precedence["+"] = std::make_pair(2, false);
    operator_precedence["/"] = std::make_pair(3, false);
    operator_precedence["*"] = std::make_pair(3, false);
    operator_precedence["^"] = std::make_pair(4, true);

    std::vector<std::string> tokens = tokenize(expression);
    std::stack<std::string> s;
    std::queue<std::string> q;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
      std::string token = *it;
      if (operator_precedence.count(token)) {
        while (!s.empty() && operator_precedence.count(s.top()) &&
               ((!operator_precedence[s.top()].second && operator_precedence[s.top()].first >= operator_precedence[token].first)
                || (operator_precedence[s.top()].second && operator_precedence[s.top()].first > operator_precedence[token].first))) {
          q.push(s.top()); s.pop();
        }
        s.push(token);
      } else if (token == "(") {
        s.push(token);
      } else if (token == ")") {
        while (s.top() != "(") {
          q.push(s.top()); s.pop();
        }
        s.pop();
      } else {
        // must be a number
        q.push(token);
      }
    }
    while (!s.empty()) {
      q.push(s.top()); s.pop();
    }
    return q;
  }

  double evaluate_expression(std::queue<std::string> expression) {
    std::stack<double> operands;
    while (!expression.empty()) {
      std::string next = expression.front(); expression.pop();
      if (next == "^") {
        double a = operands.top(); operands.pop();
        double b = operands.top(); operands.pop();
        operands.push(pow(b,a));
      } else if (next == "*") {
        double a = operands.top(); operands.pop();
        double b = operands.top(); operands.pop();
        operands.push(b*a);
      } else if (next == "/") {
        double a = operands.top(); operands.pop();
        double b = operands.top(); operands.pop();
        operands.push(b/a);
      } else if (next == "+") {
        double a = operands.top(); operands.pop();
        double b = operands.top(); operands.pop();
        operands.push(b+a);
      } else if (next == "-") {
        double a = operands.top(); operands.pop();
        double b = operands.top(); operands.pop();
        operands.push(b-a);
      } else {
        operands.push(std::stod(next));
      }
    }
    return operands.top();
  }
}
