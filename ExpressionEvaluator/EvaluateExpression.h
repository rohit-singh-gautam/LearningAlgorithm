#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>

class OperatorNode;
class OperandNode;

struct TypeID {
	int typeId;
	template <size_t size>
	constexpr TypeID(const char (&typeIdCh)[size]) : typeId { (size >= 1 ? typeIdCh[0] : 0) + (size >= 2 ? typeIdCh[1] << 8 : 0) + (size >= 3 ? typeIdCh[2] << 16: 0) + (size >= 4 ? typeIdCh[3] << 24 : 0)} { }

	constexpr operator int() const { return typeId; }
};

class BaseExpression;
std::vector<BaseExpression *> TokenizeToObject(const std::string &InfixExpression);
BaseExpression *ParseInfixToken(std::vector<BaseExpression *> &tokens);
std::ostream &operator<<(std::ostream &os, const std::vector<BaseExpression *> &tokens);

class BaseExpression {
protected:
	const std::string OriginalString;
public:
	constexpr BaseExpression(const std::string &originalString) : OriginalString(originalString) { }
	constexpr BaseExpression(std::string &&originalString) : OriginalString(originalString) { }
	constexpr BaseExpression() : OriginalString { } { }
	constexpr virtual const std::vector<BaseExpression *> &GetChildren() const = 0;
	constexpr virtual std::vector<BaseExpression *> &GetChildren() = 0;
	constexpr virtual double GetValue() const = 0;
	constexpr virtual const std::string &ToString() const { return OriginalString; };
	constexpr virtual double Evaluate() const = 0;
	constexpr virtual bool IsLeaf() const = 0;
	constexpr virtual void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) = 0;
	constexpr virtual int getType() const { return typeId; };
	constexpr virtual bool isType(int type) const { return BaseExpression::typeId == type; };

	static constexpr BaseExpression *Parse(std::string InfixExpression, bool bDisplayInfix) {
		auto InfixToken = TokenizeToObject(InfixExpression);
		if (bDisplayInfix) std::cout << InfixToken;

		BaseExpression *FinalTree = ParseInfixToken(InfixToken);
		
		return FinalTree;
	}

	static constexpr const TypeID typeId { "base" };
};

void DisplayExpressionTree(BaseExpression *root);

class OperandNode : public BaseExpression {
public:
	using BaseExpression::BaseExpression;
	constexpr void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override {
		Operands.push(this);
	}
	constexpr bool isType(int type) const override {
		return OperandNode::typeId == type || BaseExpression::isType(type);
	}



	static constexpr const TypeID typeId { "Oprn" };
};

class OperatorNode : public OperandNode {
public:
	using OperandNode::OperandNode;
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override {
		return OperandNode::typeId == type || OperandNode::isType(type);
	}

	constexpr virtual int GetPrecedence() const = 0;
	constexpr double GetValue() const override { throw new std::domain_error("Operator cannot have value"); }
	constexpr const std::vector<BaseExpression *> &GetChildren() const override { throw new std::domain_error("Temporary node, does not have child"); }
	constexpr std::vector<BaseExpression *> &GetChildren() override { throw new std::domain_error("Temporary node, does not have child"); }
	constexpr double Evaluate() const override { throw new std::domain_error("Cannot evaluate operator"); }

	enum Direction {
		InvalidDirection,
		LeftToRight,
		RightToLeft
	};
	constexpr virtual Direction GetDirection() const = 0;
	constexpr void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override
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

	constexpr bool AmIHigherPrecedence(OperatorNode *rhs) const {
		int left = this->GetPrecedence();
		int right = rhs->GetPrecedence();

		if (left == right) return rhs->GetDirection() == LeftToRight;
		return left > right;
	}
	static constexpr const TypeID typeId { "oprt" };
};


class BinaryOperator : public OperatorNode {
protected:
	std::vector<BaseExpression *> Children { 2, nullptr };
	constexpr void ThrowInvalid() const {
		if (Children[0] == nullptr || Children[1] == nullptr) {
			throw new std::domain_error("Binary operator requires both left and right operator");
		}
	}
public:
	using OperatorNode::OperatorNode;
	constexpr const BaseExpression * GetLeft() const { return Children[0]; }
	constexpr const BaseExpression * GetRight() const { return Children[1]; };
	constexpr BaseExpression * GetLeft() { return Children[0]; }
	constexpr BaseExpression * GetRight() { return Children[1]; };
	constexpr const std::vector<BaseExpression *> &GetChildren() const override { return Children; }
	constexpr std::vector<BaseExpression *> &GetChildren() override { return Children; }
	constexpr bool IsLeaf() const override { return false; } // Binary operator cannot be leaf
	constexpr bool isType(int type) const override { return BinaryOperator::typeId == type || OperandNode::isType(type); }
	constexpr int getType() const override { return typeId; }
	static constexpr const TypeID typeId { "biop" };
};

class NumberNode : public OperandNode {
protected:
	const double Value;
public:
	constexpr NumberNode(const std::string &number) : OperandNode { number }, Value { std::stod(number) } { }

	constexpr const std::vector<BaseExpression *> &GetChildren() const override { throw std::domain_error("Number Node does not have children"); }
	constexpr std::vector<BaseExpression *> &GetChildren() override { throw std::domain_error("Number Node does not have children"); }

	constexpr double GetValue() const override { return Value; }
	constexpr double Evaluate() const override { return Value; };
	constexpr bool IsLeaf() const override { return true; }
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override {
		return NumberNode::typeId == type || OperandNode::isType(type);
	}
	static constexpr const TypeID typeId { "bumr" };
};

class PlusOperator : public BinaryOperator {
	static constexpr const std::string PlusString { "+" };
public:
	using BinaryOperator::BinaryOperator;
	constexpr const std::string &ToString() const override { return PlusString; }
	constexpr double Evaluate() const override {
		ThrowInvalid();
		return Children[0]->Evaluate() + Children[1]->Evaluate();
	}
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override {
		return PlusOperator::typeId == type || BinaryOperator::isType(type);
	}
	constexpr int GetPrecedence() const override { return 40; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "+opr" };
};

class MinusOperator : public BinaryOperator {
	static constexpr const std::string MinusString { "-" };
public:
	using BinaryOperator::BinaryOperator;
	constexpr const std::string &ToString() const override { return MinusString; }
	constexpr double Evaluate() const override {
		ThrowInvalid();
		return Children[0]->Evaluate() - Children[1]->Evaluate();
	}
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return MinusOperator::typeId == type || BinaryOperator::isType(type); }
	constexpr int GetPrecedence() const override { return 40; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "-opr" };
};

class MultiplyOperator : public BinaryOperator {
	static constexpr const std::string MultiplyString { "*" };
public:
	using BinaryOperator::BinaryOperator;
	constexpr const std::string &ToString() const override { return MultiplyString; }
	constexpr double Evaluate() const override {
		ThrowInvalid();
		return Children[0]->Evaluate() * Children[1]->Evaluate();
	}
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return MultiplyOperator::typeId == type || BinaryOperator::isType(type); }
	constexpr int GetPrecedence() const override { return 50; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "*opr" };
};

class DivideOperator : public BinaryOperator {
	static constexpr const std::string DivideString { "/" };
public:
	using BinaryOperator::BinaryOperator;
	constexpr const std::string &ToString() const override { return DivideString; }
	constexpr double Evaluate() const override {
		ThrowInvalid();
		return Children[0]->Evaluate() / Children[1]->Evaluate();
	}
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return DivideOperator::typeId == type || BinaryOperator::isType(type);}
	constexpr int GetPrecedence() const override { return 50; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "/opr" };
};

class BracketNode : public OperatorNode {
public:
	using OperatorNode::OperatorNode;
	constexpr bool IsLeaf() const override { return true; }
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return BracketNode::typeId == type || OperatorNode::isType(type);}
	constexpr int GetPrecedence() const override { return 0; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "()op" };
};

class BracketOpenNode : public BracketNode {
	static constexpr const std::string BracketOpenString { "(" };
public:
	using BracketNode::BracketNode;
	constexpr const std::string &ToString() const override { return BracketOpenString; }
	constexpr void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override { Operators.push(this); }
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return BracketOpenNode::typeId == type || BracketNode::isType(type);}
	static constexpr const TypeID typeId { "(opr" };
};

class BracketCloseNode : public BracketNode {
	static constexpr const std::string BracketCloseString { ")" };
public:
	using BracketNode::BracketNode;
	constexpr const std::string &ToString() const override { return BracketCloseString; }
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return BracketCloseNode::typeId == type || BracketNode::isType(type);}
	constexpr void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override
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
	static constexpr const TypeID typeId { ")opr" };
};

class EndOfExpressionNode : public BracketNode {
	static constexpr const std::string EndOfExpressionString { "#" };
public:
	using BracketNode::BracketNode;
	constexpr const std::string &ToString() const override { return EndOfExpressionString; }
	constexpr int getType() const override { return typeId; }
	constexpr bool isType(int type) const override { return EndOfExpressionNode::typeId == type || BracketNode::isType(type);}
	constexpr int GetPrecedence() const override { return 0; }
	constexpr Direction GetDirection() const override { return LeftToRight; }
	static constexpr const TypeID typeId { "endx" };
};
