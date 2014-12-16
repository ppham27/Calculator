#include <iostream>

#include <stack>
#include <vector>
#include <string>

#include "Calculator.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(evaluate_expression, default) {
  ASSERT_DOUBLE_EQ(7,calc::evaluate_expression(calc::parse_expression("3+4")));
  ASSERT_DOUBLE_EQ(1.4,calc::evaluate_expression(calc::parse_expression("0.75+0.65")));
  ASSERT_DOUBLE_EQ(8,calc::evaluate_expression(calc::parse_expression("4*2")));
  ASSERT_DOUBLE_EQ(81,calc::evaluate_expression(calc::parse_expression("3^4")));  
  ASSERT_DOUBLE_EQ(1.3333333333333333,calc::evaluate_expression(calc::parse_expression("4/3")));
  ASSERT_DOUBLE_EQ(3.0001220703125,calc::evaluate_expression(calc::parse_expression("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3")));
  ASSERT_DOUBLE_EQ(1000,calc::evaluate_expression(calc::parse_expression("(4.3 + 5.7)^3")));
}

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
  std::string expression7 = "0.75+0.65";
  std::vector<std::string> expected_expression7{"0.75","+","0.65"};
  std::string expression8 = "(4.3 + 5.7)^3";
  std::vector<std::string> expected_expression8{"(","4.3","+","5.7",")","^","3"};
  ASSERT_EQ(expected_expression0, calc::tokenize(expression0));  
  ASSERT_EQ(expected_expression1, calc::tokenize(expression1));
  ASSERT_EQ(expected_expression2, calc::tokenize(expression2));
  ASSERT_EQ(expected_expression3, calc::tokenize(expression3));
  ASSERT_EQ(expected_expression4, calc::tokenize(expression4));
  ASSERT_EQ(expected_expression5, calc::tokenize(expression5));
  ASSERT_EQ(expected_expression6, calc::tokenize(expression6));
  ASSERT_EQ(expected_expression7, calc::tokenize(expression7));
  ASSERT_EQ(expected_expression8, calc::tokenize(expression8));
}


TEST(parse_expression, default) {
  std::string expression0 = "3+4";
  std::queue<std::string> parsed_expression0 = calc::parse_expression(expression0);
  ASSERT_EQ(3, parsed_expression0.size());
  std::vector<std::string> expected_expression0{"3","4","+"};
  for (auto it = expected_expression0.begin(); it != expected_expression0.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression0.front());
    parsed_expression0.pop();
  }
  
  std::string expression1 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
  std::queue<std::string> parsed_expression1 = calc::parse_expression(expression1);
  ASSERT_EQ(13, parsed_expression1.size());
  std::vector<std::string> expected_expression1{"3","4","2","*","1","5","-","2","3","^","^","/","+"};
  for (auto it = expected_expression1.begin(); it != expected_expression1.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression1.front());
    parsed_expression1.pop();
  }

  std::string expression2 = "5 - 2";
  std::queue<std::string> parsed_expression2 = calc::parse_expression(expression2);
  ASSERT_EQ(3, parsed_expression2.size());
  std::vector<std::string> expected_expression2{"5","2","-"};
  for (auto it = expected_expression2.begin(); it != expected_expression2.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression2.front());
    parsed_expression2.pop();
  }
  
  std::string expression3 = "5 + -2";
  std::queue<std::string> parsed_expression3 = calc::parse_expression(expression3);
  ASSERT_EQ(3, parsed_expression3.size());
  std::vector<std::string> expected_expression3{"5","-2","+"};
  for (auto it = expected_expression3.begin(); it != expected_expression3.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression3.front());
    parsed_expression3.pop();
  }

  std::string expression4 = "5--2";
  std::queue<std::string> parsed_expression4 = calc::parse_expression(expression4);
  ASSERT_EQ(3, parsed_expression4.size());
  std::vector<std::string> expected_expression4{"5","-2","-"};
  for (auto it = expected_expression4.begin(); it != expected_expression4.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression4.front());
    parsed_expression4.pop();
  }

  std::string expression5 = "0.75+0.65";
  std::queue<std::string> parsed_expression5 = calc::parse_expression(expression5);
  ASSERT_EQ(3, parsed_expression5.size());
  std::vector<std::string> expected_expression5{"0.75","0.65","+"};
  for (auto it = expected_expression5.begin(); it != expected_expression5.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression5.front());
    parsed_expression5.pop();
  }

  std::string expression6 = "(4.3 + 5.7)^3";
  std::queue<std::string> parsed_expression6 = calc::parse_expression(expression6);
  ASSERT_EQ(5, parsed_expression6.size());
  std::vector<std::string> expected_expression6{"4.3","5.7","+","3","^"};
  for (auto it = expected_expression6.begin(); it != expected_expression6.end(); ++it) {
    ASSERT_EQ(*it, parsed_expression6.front());
    parsed_expression6.pop();
  }  
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();    
}
