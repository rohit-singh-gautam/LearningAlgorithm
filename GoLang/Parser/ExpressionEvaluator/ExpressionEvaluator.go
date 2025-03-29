package main

import "fmt"

// Grammar
// Expr: Term '+' Expr | Term '-' Expr | Term
// Term: Factor '*' Term | Factor '/' Term | Factor
// Factor: '(' Expr ')' | Number
// Number: [0-9]+
// This is a simple expression evaluator that can handle basic arithmetic operations.

// ExpressionEvaluator evaluates a mathematical expression represented as a string.
type ExpressionEvaluator struct {
	expression string
	currentPos int
}

// NewExpressionEvaluator creates a new ExpressionEvaluator with the given expression.
func NewExpressionEvaluator(expression string) *ExpressionEvaluator {
	return &ExpressionEvaluator{expression: expression, currentPos: 0}
}

// SetExpression sets a new expression for the evaluator.
func (expr *ExpressionEvaluator) SkipWhiteSpace() {
	for expr.currentPos < len(expr.expression) && (expr.expression[expr.currentPos] == ' ' || expr.expression[expr.currentPos] == '\t') {
		expr.currentPos++
	}
}

func (expr *ExpressionEvaluator) ParseNumber() int {
	var ret int = 0
	for expr.currentPos < len(expr.expression) && expr.expression[expr.currentPos] >= '0' && expr.expression[expr.currentPos] <= '9' {
		ret = ret*10 + int(expr.expression[expr.currentPos]) - '0'
		expr.currentPos++
	}
	expr.SkipWhiteSpace()
	return ret
}

func (expr *ExpressionEvaluator) ParseFactor() int {
	if expr.expression[expr.currentPos] == '(' {
		expr.currentPos++
		ret := expr.ParseExpr()
		if expr.expression[expr.currentPos] != ')' {
			panic("Expecting bracket close")
		}
		expr.currentPos++
		expr.SkipWhiteSpace()
		return ret
	} else if expr.expression[expr.currentPos] >= '0' && expr.expression[expr.currentPos] <= '9' {
		return expr.ParseNumber()
	} else {
		panic("Expecting ( or number got " + string(expr.expression[expr.currentPos]))
	}
}

func (expr *ExpressionEvaluator) ParseTerm() int {
	ret := expr.ParseFactor()
	if expr.currentPos >= len(expr.expression) {
		return ret
	}
	for expr.currentPos < len(expr.expression) && (expr.expression[expr.currentPos] == '*' || expr.expression[expr.currentPos] == '/') {
		ch := expr.expression[expr.currentPos]
		expr.currentPos++
		expr.SkipWhiteSpace()
		rhs := expr.ParseFactor()
		if ch == '*' {
			ret *= rhs
		} else {
			ret /= rhs
		}
	}
	return ret
}

func (expr *ExpressionEvaluator) ParseExpr() int {
	expr.SkipWhiteSpace()
	ret := expr.ParseTerm()
	if expr.currentPos >= len(expr.expression) {
		return ret
	}
	for expr.currentPos < len(expr.expression) && (expr.expression[expr.currentPos] == '+' || expr.expression[expr.currentPos] == '-') {
		ch := expr.expression[expr.currentPos]
		expr.currentPos++
		expr.SkipWhiteSpace()
		rhs := expr.ParseTerm()
		if ch == '+' {
			ret += rhs
		} else {
			ret -= rhs
		}
	}
	return ret
}

func main() {
	exprlist := []struct {
		input    string
		expected int
	}{
		{"1+2", 3},
		{"1-2", -1},
		{"1*2", 2},
		{"1/2", 0},
		{"1+2*3", 7},
		{"(1+2)*3", 9},
		{"(1+2)/3", 1},
		{"(1+2)*3-4", 5},
		{"(1+2)*3-4/2", 7},
		{"(1+2)*3-4/2+5", 12},
		{"(1+2)*3-4/2+5*6", 37},
		{"(1+2)*3-4/2+5*6-7", 30},
		{"(1+2)*3-4/2+5*6-7/7", 36},
		{"(1+2)*3-4/2+5*6-7/7+9", 45},
		{"(1+2)*3-4/2+5*6-7/7+9*10", 126},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11", 115},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11", 125},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13", 138},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13*14", 307},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13*14-15", 292},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13*14-15/15", 306},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13*14-15/15+17", 323},
		{"(1+2)*3-4/2+5*6-7/7+9*10-11/11+13*14-15/15+17*18", 612},
		{"((((1+2)*(2+3) + (1+1)) * (1*(1+3)))) * (1+1)", 136},
		{"((((1+2)*(2+3) + (1+1)) * (1*(1+3)))) * (1+1) + 5", 141},
		{"((((1+2)*(2+3) + (1+1)) * (1*(1+3)))) * (1+1) + 5 - 6", 135},
	}

	for _, test := range exprlist {
		evaluator := NewExpressionEvaluator(test.input)
		result := evaluator.ParseExpr()
		fmt.Println("Evaluating: ", test.input, " Result: ", result, " Expected: ", test.expected)
		if result != test.expected {
			panic("Test failed")
		}
	}
}
