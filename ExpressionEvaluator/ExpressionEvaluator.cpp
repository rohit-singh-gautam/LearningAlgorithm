// ExpressionEvaluator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "EvaluateExpression.h"
#include <iostream>


int main(int argc, char *argv[])
{
	const std::string explist[] = {
		"1 + 2",
		"5*2+4*3*(5-8+5)+6+(3*2+6*7)",
		"5.0 + 4.0000 -         (002.0000000 * 0004)",
		"5.0 + 4.0000 - 3 - 2 * 6",
		"3 - 2",
		"2 * 3",
		"6 / 4",
		"1.4*2.6+3.2+02.39+2.5*3/2",
		"10 + 20",
		"1.0 + 2.20"
	};

	for (const auto &exp : explist) {
		std::cout << "Expression: " << exp << std::endl;
		auto ExpObject = BaseExpression::Parse(exp, true);
		std::cout << "Expression Tree" << std::endl;
		DisplayExpressionTree(ExpObject);
		double value = ExpObject->Evaluate();
		std::cout << "Value: " << value << std::endl;
		std::cout << "---------------------------------------" << std::endl;
	}

	return 0;
}
