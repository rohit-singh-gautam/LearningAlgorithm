cmake_minimum_required(VERSION 3.16)

project(ExpressionEvaluator)

add_executable(ExpressionEvaluator ExpressionEvaluator.cpp EvaluateExpression.cpp DisplayHelper.cpp)

set_property(TARGET ExpressionEvaluator PROPERTY CXX_STANDARD 23)
