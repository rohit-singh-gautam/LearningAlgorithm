cmake_minimum_required(VERSION 3.16)

if (UNIX)
add_compile_options(-Wall -Werror -Wpedantic -Wextra -Weffc++ -Wsuggest-override) # -fanalyzer
elseif (MSVC)
add_compile_options(/W4 /WX)
endif()

add_executable(ExpressionEvaluator ExpressionEvaluator.cpp EvaluateExpression.cpp DisplayHelper.cpp)

target_compile_features(ExpressionEvaluator PRIVATE cxx_std_23)
