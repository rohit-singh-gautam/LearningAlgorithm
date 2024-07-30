#pragma once
#include <string>
#include <vector>
#include <stack>

class OperatorNode;
class OperandNode;

struct TypeID {
	int typeId;
	template <size_t size>
	constexpr TypeID(const char (&typeIdCh)[size]) : typeId { (size >= 1 ? typeIdCh[0] : 0) + (size >= 2 ? typeIdCh[1] << 8 : 0) + (size >= 3 ? typeIdCh[2] << 16: 0) + (size >= 4 ? typeIdCh[3] << 24 : 0)} { }

	constexpr operator int() const { return typeId; }
};

class BaseExpression {
protected:
	std::string OriginalString;
public:
	BaseExpression(std::string originalString);
	virtual std::vector<BaseExpression *> &GetChildren() = 0;
	virtual double GetValue() = 0;
	virtual const std::string &ToString() = 0;
	virtual double Evaluate() = 0;
	virtual bool IsLeaf() = 0;
	virtual void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) = 0;
	virtual int getType() const;
	virtual bool isType(int type);

	static BaseExpression *Parse(std::string InfixExpression, bool bDisplayInfix);

	static constexpr const TypeID typeId { "base" };
};

void DisplayExpressionTree(BaseExpression *root);

class OperandNode : public BaseExpression {
public:
	OperandNode(std::string op);
	int getType() const override;
	void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override;
	bool isType(int type) override;
};

class OperatorNode : public OperandNode {
public:
	OperatorNode(std::string op);
	int getType() const override;
	bool isType(int type) override;
	virtual int GetPrecedence() = 0;

	enum Direction {
		InvalidDirection,
		LeftToRight,
		RightToLeft
	};
	virtual Direction GetDirection() = 0;
	void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override;

	bool AmIHigherPrecedence(OperatorNode *rhs);
	static constexpr const TypeID typeId { "oprt" };
};


class BinaryOperator : public OperatorNode {
protected:
	std::vector<BaseExpression *> Children;
	void ThrowInvalid();
public:
	BinaryOperator(std::string op);
	BaseExpression * GetLeft();
	BaseExpression * GetRight();
	std::vector<BaseExpression *> &GetChildren();
	double GetValue();
	bool IsLeaf();
	bool isType(int type) override;
	int getType() const override;
	static constexpr const TypeID typeId { "biop" };
	
};

class NumberNode : public OperandNode {
protected:
	double Value;
public:
	NumberNode(std::string number);
	std::vector<BaseExpression *> &GetChildren();
	double GetValue();
	const std::string &ToString();
	double Evaluate();
	bool IsLeaf();
	int getType() const override;
	bool isType(int type) override;
	static constexpr const TypeID typeId { "bumr" };
};

class PlusOperator : public BinaryOperator {
	static const std::string PlusString;
public:
	PlusOperator(std::string op);
	const std::string &ToString();
	double Evaluate();
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "+opr" };
};

class MinusOperator : public BinaryOperator {
	static const std::string MinusString;
public:
	MinusOperator(std::string op);
	const std::string &ToString();
	double Evaluate();
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "-opr" };
};

class MultiplyOperator : public BinaryOperator {
	static const std::string MultiplyString;
public:
	MultiplyOperator(std::string op);
	const std::string &ToString();
	double Evaluate();
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "*opr" };
};

class DivideOperator : public BinaryOperator {
	static const std::string DivideString;
public:
	DivideOperator(std::string op);
	const std::string &ToString();
	double Evaluate();
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "/opr" };
};

class BracketNode : public OperatorNode {
public:
	BracketNode(std::string br);
	std::vector<BaseExpression *> &GetChildren();
	double GetValue();
	double Evaluate();
	bool IsLeaf();
	int getType() const override;
	bool isType(int type) override;
	static constexpr const TypeID typeId { "()op" };
};

class BracketOpenNode : public BracketNode {
	static const std::string BracketOpenString;
public:
	BracketOpenNode(std::string op);
	const std::string &ToString();
	void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override;
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "(opr" };
};

class BracketCloseNode : public BracketNode {
	static const std::string BracketCloseString;
public:
	BracketCloseNode(std::string op);
	const std::string &ToString();
	int getType() const override;
	bool isType(int type) override;
	void ProcessToken(std::stack<OperatorNode *> &Operators, std::stack<OperandNode *> &Operands) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { ")opr" };
};

class EndOfExpressionNode : public BracketNode {
	static const std::string EndOfExpressionString;
public:
	EndOfExpressionNode();
	const std::string &ToString();
	int getType() const override;
	bool isType(int type) override;
	int GetPrecedence();
	Direction GetDirection();
	static constexpr const TypeID typeId { "endx" };
};
