#include "EvaluateExpression.h"
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

void GetExpressionTreeParameter(BaseExpression *root, int &maxstring, int &height) {
	maxstring = 0;
	height = 0;
	if (root == nullptr) return;

	std::queue<BaseExpression *> nodes;
	nodes.push(root);
	while (!nodes.empty()) {
		height++;
		size_t count = nodes.size();
		for (size_t i = 0; i < count; i++) {
			BaseExpression *curr = nodes.front();
			maxstring = std::max(maxstring, (int)curr->ToString().size());
			nodes.pop();
			if (curr->isType(BinaryOperator::typeId)) {
				auto currop = static_cast<BinaryOperator *>(curr);
				auto left = currop->GetLeft();
				auto right = currop->GetRight();
				if (left != nullptr) nodes.push(left);
				if (right != nullptr) nodes.push(right);
			}
		}
	}
}

std::string DisplayCenter(BaseExpression *root, const auto width) {
	const std::string &text = root == nullptr ? "" : root->ToString();
	auto totalpad = width - text.size() + 1;
	auto leftpad = (totalpad - 1) / 2;
	auto rightpad = totalpad / 2;
	return std::string(leftpad, ' ') + text + std::string(rightpad, ' ');
}

void TrimEnd(std::string &text) {
	while (text.back() == ' ') text.pop_back();
}

void DisplayExpressionTree(BaseExpression *root, auto maxstring, auto height) {
	if (root == nullptr) return;

	auto currwidth = (maxstring + 2) * (1 << (height - 1));

	std::queue<BaseExpression *> nodes;
	nodes.push(root);
	size_t nullcount = 0;
	while (!nodes.empty() && nullcount < nodes.size()) {
		auto count = nodes.size();
		nullcount = 0;
		std::string text;
		for (int i = 0; i < count; i++) {
			BaseExpression *curr = nodes.front();
			nodes.pop();
			text += DisplayCenter(curr, currwidth);

			BaseExpression *left = nullptr;
			BaseExpression *right = nullptr;
			if (curr != nullptr && curr->isType(BinaryOperator::typeId)) {
				auto currop = static_cast<BinaryOperator *>(curr);
				left = currop->GetLeft();
				right = currop->GetRight();
			}
			nullcount += (left == nullptr) + (right == nullptr);
			nodes.push(left);
			nodes.push(right);
		}
		TrimEnd(text);
		std::cout << text << std::endl;
		currwidth >>= 1;
	}
}

void DisplayExpressionTree(BaseExpression *root) {
	int height;
	int maxstring;
	GetExpressionTreeParameter(root, maxstring, height);
	DisplayExpressionTree(root, maxstring, height);
}