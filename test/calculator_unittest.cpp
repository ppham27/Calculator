
#include <stack>
#include <vector>
#include <string>

#include "Calculator.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(tokenize, default) {
  std::string expression0 = "3+4";
  std::vector<std::string> expected_expression0{"3","+","4"};
  std::string expression1 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
  std::vector<std::string> expected_expression1{"3","+","4","*","2","/","(","1","-","5",")","^","2","^","3"};
  std::string expression2 = "5 - 2";
  std::vector<std::string> expected_expression2{"5","-","2"};
  std::string expression3 = "5 + -2";
  std::vector<std::string> expected_expression3{"5","+","-2"};
  std::string expression4 = "5--2";
  std::vector<std::string> expected_expression4{"5","-","-2"};
  std::string expression5 = "5-2";
  std::vector<std::string> expected_expression5{"5","-","2"};
  std::string expression6 = "-5+2";
  std::vector<std::string> expected_expression6{"-5","+","2"};
  ASSERT_EQ(expected_expression0, calc::tokenize(expression0));  
  ASSERT_EQ(expected_expression1, calc::tokenize(expression1));
  ASSERT_EQ(expected_expression2, calc::tokenize(expression2));
  ASSERT_EQ(expected_expression3, calc::tokenize(expression3));
  ASSERT_EQ(expected_expression4, calc::tokenize(expression4));
  ASSERT_EQ(expected_expression5, calc::tokenize(expression5));
  ASSERT_EQ(expected_expression6, calc::tokenize(expression6));
}


TEST(parse_expression, default) {
  std::string expression0 = "3+4";
  std::stack<std::string> parsed_expression0 = calc::parse_expression(expression0);
  ASSERT_EQ(3, parsed_expression0.size());
  std::vector<std::string> expected_expression0{"3","4","+"};
  for (auto it = expected_expression0.begin(); it != expected_expression0.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression0.top());
    parsed_expression0.pop();
  }
  
  std::string expression1 = "3 + 4 * 2 / ( 1 − 5 ) ^ 2 ^ 3";
  std::stack<std::string> parsed_expression1 = calc::parse_expression(expression1);
  ASSERT_EQ(13, parsed_expression1.size());
  std::vector<std::string> expected_expression1{"3","4","2","*","1","5","2","3","^","^","/","+"};
  for (auto it = expected_expression1.begin(); it != expected_expression1.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression1.top());
    parsed_expression1.pop();
  }

  std::string expression2 = "5 - 2";
  std::stack<std::string> parsed_expression2 = calc::parse_expression(expression2);
  ASSERT_EQ(3, parsed_expression2.size());
  std::vector<std::string> expected_expression2{"5","2","-"};
  for (auto it = expected_expression2.begin(); it != expected_expression2.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression2.top());
    parsed_expression2.pop();
  }
  
  std::string expression3 = "5 + -2";
  std::stack<std::string> parsed_expression3 = calc::parse_expression(expression3);
  ASSERT_EQ(3, parsed_expression3.size());
  std::vector<std::string> expected_expression3{"5","-2","+"};
  for (auto it = expected_expression3.begin(); it != expected_expression3.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression3.top());
    parsed_expression3.pop();
  }

  std::string expression4 = "5--2";
  std::stack<std::string> parsed_expression4 = calc::parse_expression(expression4);
  ASSERT_EQ(3, parsed_expression4.size());
  std::vector<std::string> expected_expression4{"5","-2","-"};
  for (auto it = expected_expression4.begin(); it != expected_expression4.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression4.top());
    parsed_expression4.pop();
  }  
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();    
}
