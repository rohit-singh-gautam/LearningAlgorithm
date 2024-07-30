#include "EvaluateExpression.h"
#include <cctype>
#include <iostream>
#include <stack>
#include <exception>


void NormalizeNumber(std::string &num) {
	//Remove traling 0;
	while (num.back() == '0') num.pop_back();

	//Count decimal
	int cntpoint = 0;
	for (char c : num) if (c == '.') cntpoint++;
	if (cntpoint > 1) {
		throw std::domain_error("Numbers cannot have two decimal point");
	}

	//Remove trailing .
	if (num.back() == '.') num.pop_back();

	//Remove leading 0
	while (num.size() >= 2 && num.front() == '0') {
		num.erase(0, 1);
	}
}

std::vector<BaseExpression *> TokenizeToObject(std::string InfixExpression) {
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
	states state = newstate;
	size_t i = 0;
	while(true) {
		// Skip white space
		while (i < n && isspace(InfixExpression[i])) i++;
		if (i >= n) break;

		size_t j = i;
		//Find what character it is
		char c = InfixExpression[i];
		if (isdigit(c)) {
			while (i < n && isdigit(InfixExpression[i]) || InfixExpression[i] == '.') i++;
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
	std::stack<OperatorNode *> Operators;
	std::stack<OperandNode *> Operands;

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

BaseExpression::BaseExpression(std::string originalString) : OriginalString(originalString)
{
	// Empty function.
}

void DisplayToken(const std::vector<BaseExpression *> &tokens) {
	std::cout << "Tokens: ";
	for (const auto &token : tokens) {
		std::cout << token->ToString() << " ";
	}
	std::cout << std::endl;
}

int BaseExpression::getType() const
{
	return typeId;
}

bool BaseExpression::isType(int type) {
	return BaseExpression::typeId == type;
}

BaseExpression *BaseExpression::Parse(std::string InfixExpression, bool bDisplayInfix) {
	auto InfixToken = TokenizeToObject(InfixExpression);
	if (bDisplayInfix) DisplayToken(InfixToken);

	BaseExpression *FinalTree = ParseInfixToken(InfixToken);
	
	return FinalTree;
}

void OperandNode::ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands)
{
	Operands.push(this);
}

NumberNode::NumberNode(std::string number) : OperandNode(number)
{
	Value = std::stod(number);
}

std::vector<BaseExpression *>& NumberNode::GetChildren()
{
	static std::vector<BaseExpression *> EmptyVector;
	return EmptyVector;
}

double NumberNode::GetValue()
{
	return Value;
}

const std::string &NumberNode::ToString()
{
	return OriginalString;
}

double NumberNode::Evaluate()
{
	return Value;
}

bool NumberNode::IsLeaf()
{
	return true;
}

int NumberNode::getType() const
{
	return typeId;
}

bool NumberNode::isType(int type)
{
	return NumberNode::typeId == type || OperandNode::isType(type);
}

bool OperandNode::isType(int type) {
	return OperandNode::typeId == type || BaseExpression::isType(type);
}

void OperatorNode::ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands)
{
	while (!Operators.empty() && Operators.top()->AmIHigherPrecedence(this)) {
		OperatorNode *Op = Operators.top();
		Operators.pop();
		auto &childrens = Op->GetChildren();
		for (size_t i = childrens.size(); i > 0; i--) {
			if (Operands.empty()) {
				throw std::domain_error("Insufficient operands, wrong syntax");
			}

			if (childrens[i - 1] != nullptr) {
				throw std::domain_error("Operands already present, wrong syntax or internal error");
			}

			childrens[i - 1] = Operands.top();
			Operands.pop();
		}
		Operands.push(Op);
	}
	Operators.push(this);
}

BaseExpression * BinaryOperator::GetLeft()
{
	return Children[0];
}

BaseExpression * BinaryOperator::GetRight()
{
	return Children[1];
}

void BinaryOperator::ThrowInvalid()
{
	if (Children[0] == nullptr || Children[1] == nullptr) {
		throw new std::domain_error("Binary operator requires both left and right operator");
	}
}

BinaryOperator::BinaryOperator(std::string op) : OperatorNode(op), Children(2, nullptr)
{
}

std::vector<BaseExpression*>& BinaryOperator::GetChildren()
{
	return Children;
}

double BinaryOperator::GetValue()
{
	throw new std::domain_error("Operator cannot have value");
}

bool BinaryOperator::IsLeaf()
{
	return Children[0] == nullptr && Children[1] == nullptr;
}

bool BinaryOperator::isType(int type)
{
	return BinaryOperator::typeId == type || OperandNode::isType(type);
}

int BinaryOperator::getType() const
{
	return typeId;
}

const std::string PlusOperator::PlusString = "+";
PlusOperator::PlusOperator(std::string op) : BinaryOperator(op)
{
}

const std::string &PlusOperator::ToString()
{
	return PlusString;
}

double PlusOperator::Evaluate()
{
	ThrowInvalid();
	return Children[0]->Evaluate() + Children[1]->Evaluate();
}

int PlusOperator::getType() const
{
	return typeId;
}

bool PlusOperator::isType(int type)
{
	return PlusOperator::typeId == type || BinaryOperator::isType(type);
}

int PlusOperator::GetPrecedence()
{
	return 40;
}

OperatorNode::Direction PlusOperator::GetDirection()
{
	return LeftToRight;
}

const std::string MinusOperator::MinusString = "-";
MinusOperator::MinusOperator(std::string op) : BinaryOperator(op)
{
}

const std::string & MinusOperator::ToString()
{
	return MinusString;
}

double MinusOperator::Evaluate()
{
	ThrowInvalid();
	return Children[0]->Evaluate() - Children[1]->Evaluate();
}

int MinusOperator::getType() const
{
	return (int)*"-opr";
}

bool MinusOperator::isType(int type)
{
	return MinusOperator::typeId == type || BinaryOperator::isType(type);
}

int MinusOperator::GetPrecedence()
{
	return 40;
}

OperatorNode::Direction MinusOperator::GetDirection()
{
	return LeftToRight;
}

const std::string MultiplyOperator::MultiplyString = "*";
MultiplyOperator::MultiplyOperator(std::string op) : BinaryOperator(op)
{
}

const std::string & MultiplyOperator::ToString()
{
	return MultiplyString;
}

double MultiplyOperator::Evaluate()
{
	ThrowInvalid();
	return Children[0]->Evaluate() * Children[1]->Evaluate();
}

int MultiplyOperator::getType() const
{
	return typeId;
}

bool MultiplyOperator::isType(int type)
{
	return MultiplyOperator::typeId == type || BinaryOperator::isType(type);
}

int MultiplyOperator::GetPrecedence()
{
	return 50;
}

OperatorNode::Direction MultiplyOperator::GetDirection()
{
	return LeftToRight;
}

const std::string DivideOperator::DivideString = "/";

DivideOperator::DivideOperator(std::string op) : BinaryOperator(op)
{
}

const std::string & DivideOperator::ToString()
{
	return DivideString;
}

double DivideOperator::Evaluate()
{
	ThrowInvalid();
	return Children[0]->Evaluate() / Children[1]->Evaluate();
}

int DivideOperator::getType() const
{
	return typeId;
}

bool DivideOperator::isType(int type)
{
	return DivideOperator::typeId == type || BinaryOperator::isType(type);
}

int DivideOperator::GetPrecedence()
{
	return 50;
}

OperatorNode::Direction DivideOperator::GetDirection()
{
	return LeftToRight;
}

BracketNode::BracketNode(std::string br) : OperatorNode(br)
{
}

std::vector<BaseExpression*>& BracketNode::GetChildren()
{
	throw new std::domain_error("Temporary node, does not have child");
}

double BracketNode::GetValue()
{
	throw new std::domain_error("Brackets does not have values");
}

double BracketNode::Evaluate()
{
	throw new std::domain_error("Cannot evaluate brackets");
}

bool BracketNode::IsLeaf()
{
	return true;
}

int BracketNode::getType() const
{
	return (int)*"()op";
}

bool BracketNode::isType(int type)
{
	return BracketNode::typeId == type || OperandNode::isType(type);
}

const std::string BracketOpenNode::BracketOpenString = "(";

BracketOpenNode::BracketOpenNode(std::string op) : BracketNode(op)
{
}

void BracketOpenNode::ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands)
{
	Operators.push(this);
}

const std::string & BracketOpenNode::ToString()
{
	return BracketOpenString;
}

int BracketOpenNode::getType() const
{
	return typeId;
}

bool BracketOpenNode::isType(int type)
{
	return BracketOpenNode::typeId == type || BracketNode::isType(type);
}

int BracketOpenNode::GetPrecedence()
{
	return 0;
}

OperatorNode::Direction BracketOpenNode::GetDirection()
{
	return LeftToRight;
}

const std::string BracketCloseNode::BracketCloseString = ")";

BracketCloseNode::BracketCloseNode(std::string op) : BracketNode(op)
{
}

const std::string & BracketCloseNode::ToString()
{
	return BracketCloseString;
}

int BracketCloseNode::getType() const
{
	return typeId;
}

bool BracketCloseNode::isType(int type)
{
	return BracketCloseNode::typeId == type || BracketNode::isType(type);
}

void BracketCloseNode::ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands)
{
	while (!Operators.empty() && Operators.top()->getType() != BracketOpenNode::typeId) {
		OperatorNode *Op = Operators.top();
		Operators.pop();
		auto &childrens = Op->GetChildren();
		for (size_t i = childrens.size(); i > 0; i--) {
			if (Operands.empty()) {
				throw std::domain_error("Insufficient operands, wrong syntax");
			}

			if (childrens[i - 1] != nullptr) {
				throw std::domain_error("Operands already present, wrong syntax or internal error");
			}

			childrens[i - 1] = Operands.top();
			Operands.pop();
		}
		Operands.push(Op);
	}
	if (Operators.empty() || Operators.top()->getType() != BracketOpenNode::typeId) {
		throw std::domain_error("Bracket close without open, wrong syntax");
	}
	Operators.pop();
}

int BracketCloseNode::GetPrecedence()
{
	return 0;
}

OperatorNode::Direction BracketCloseNode::GetDirection()
{
	return LeftToRight;
}

OperatorNode::OperatorNode(std::string op) : OperandNode(op)
{
}

int OperatorNode::getType() const
{
	return typeId;
}

bool OperatorNode::isType(int type)
{
	return OperandNode::typeId == type || OperandNode::isType(type);
}

bool OperatorNode::AmIHigherPrecedence(OperatorNode * rhs)
{
	int left = this->GetPrecedence();
	int right = rhs->GetPrecedence();

	if (left == right) return rhs->GetDirection() == LeftToRight;
	return left > right;
}

OperandNode::OperandNode(std::string op) : BaseExpression(op)
{
}

int OperandNode::getType() const
{
	return typeId;
}

const std::string EndOfExpressionNode::EndOfExpressionString = "#";

EndOfExpressionNode::EndOfExpressionNode() : BracketNode(EndOfExpressionString)
{
}

const std::string & EndOfExpressionNode::ToString()
{
	return EndOfExpressionString;
}

int EndOfExpressionNode::getType() const
{
	return typeId;
}

bool EndOfExpressionNode::isType(int type)
{
	return EndOfExpressionNode::typeId == type || BracketNode::isType(type);
}

int EndOfExpressionNode::GetPrecedence()
{
	return 0;
}

OperatorNode::Direction EndOfExpressionNode::GetDirection()
{
	return LeftToRight;
}
