cmake_minimum_required(VERSION 3.16)


project(ExpressionEvaluator)

add_compile_options(-Wall -Werror)

add_executable(ExpressionEvaluator ExpressionEvaluator.cpp EvaluateExpression.cpp DisplayHelper.cpp)

set_property(TARGET ExpressionEvaluator PROPERTY CXX_STANDARD 23)
