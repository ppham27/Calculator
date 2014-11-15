# CMake generated Testfile for 
# Source directory: /Users/phil/Calculator
# Build directory: /Users/phil/Calculator/build
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(CalculatorTest "test/bin/calculator_unittest")
SUBDIRS(src)
SUBDIRS(test)
