#include "EvaluateExpression.h"
#include <cctype>
#include <iostream>
#include <stack>
#include <exception>


void NormalizeNumber(std::string &num) {
	//Count decimal
	int cntpoint = 0;
	for (char c : num) if (c == '.') cntpoint++;
	if (cntpoint) {
		if (cntpoint >= 2) {
			throw std::domain_error("Numbers cannot have two decimal point");
		}
		//Remove traling zero;
		while (num.back() == '0') num.pop_back();
		//Remove trailing .
		if (num.back() == '.') num.pop_back();
	}

	//Remove leading 0
	if (num.size() >= 2) {
		decltype(num.size()) leading_zero { 0 };
		for(;leading_zero < num.size(); ++leading_zero) {
			if (num[leading_zero] != '0') break;
		}
		num.erase(0, leading_zero);
	}

	if (num.empty()) num.push_back('0');
}

std::vector<BaseExpression *> TokenizeToObject(const std::string &InfixExpression) {
	const size_t n = InfixExpression.size();
	std::vector<BaseExpression *> InfixToken;
	std::string temp;
	enum states {
		newstate,
		operatorstate,
		integerstate,
		decimalstate,
		fractionstate
	};
	size_t i = 0;
	while(true) {
		// Skip white space
		while (i < n && isspace(InfixExpression[i])) i++;
		if (i >= n) break;

		size_t j = i;
		//Find what character it is
		char c = InfixExpression[i];
		if (isdigit(c)) {
			while (i < n && (isdigit(InfixExpression[i]) || InfixExpression[i] == '.')) i++;
			std::string numberstr = InfixExpression.substr(j, i - j);
			NormalizeNumber(numberstr);
			InfixToken.push_back(new NumberNode(numberstr));
		}
		else {
			switch (c) {
			case '+':
				InfixToken.push_back(new PlusOperator(InfixExpression.substr(i, 1)));
				break;
			case '-':
				InfixToken.push_back(new MinusOperator(InfixExpression.substr(i, 1)));
				break;
			case '*':
				InfixToken.push_back(new MultiplyOperator(InfixExpression.substr(i, 1)));
				break;
			case '/':
				InfixToken.push_back(new DivideOperator(InfixExpression.substr(i, 1)));
				break;
			case '(':
				InfixToken.push_back(new BracketOpenNode(InfixExpression.substr(i, 1)));
				break;
			case ')':
				InfixToken.push_back(new BracketCloseNode(InfixExpression.substr(i, 1)));
				break;
			default:
				throw new std::domain_error("Unknown character found exception");
			}
			i++;
		}
	}

	return InfixToken;
}

BaseExpression *ParseInfixToken(std::vector<BaseExpression *> &tokens) {
	std::stack<OperatorNode *> Operators { };
	std::stack<OperandNode *> Operands { };

	if (tokens.empty()) {
		return nullptr;
	}

	if (tokens.back()->getType() != EndOfExpressionNode::typeId) {
		tokens.push_back(new EndOfExpressionNode());
	}

	for (auto token : tokens) {
		token->ProcessToken(Operators, Operands);
	}

	if (Operands.empty()) {
		throw std::domain_error("Insufficient operands, wrong syntax");
	}

	if (Operands.size() > 1) {
		throw std::domain_error("Too many operands, wrong syntax");
	}

	if (Operators.empty()) {
		throw std::domain_error("Internal error or wrong syntax, operators empty, end of expression marker not present");
	}

	if (Operators.size() > 1) {
		throw std::domain_error("Too many operators, wrong syntax or internal error");
	}

	if (typeid(*Operators.top()) != typeid(EndOfExpressionNode)) {
		throw std::domain_error("Internal error or wrong syntax, end of expression marker not present");
	}

	Operators.pop();

	BaseExpression *FinalTree = Operands.top();
	Operands.pop();
	return FinalTree;
}

std::ostream &operator<<(std::ostream &os, const std::vector<BaseExpression *> &tokens) {
	os << "Tokens: ";
	for (const auto &token : tokens) {
		os << token->ToString() << " ";
	}
	os << std::endl;

	return os;
}

