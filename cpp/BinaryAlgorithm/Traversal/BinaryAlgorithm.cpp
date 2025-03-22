// BinaryAlgorithm.cpp : Defines the entry point for the console application.
//

#include <concepts>
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& arr) {
	o << "{ ";
	if (!arr.empty()) {
		auto itr { std::begin(arr) };
		o << *itr;
		itr = std::next(itr);
		while(itr != std::end(arr)) {
			o << ", " << *itr;
			itr = std::next(itr);
		}
	}
	return o << " }";
}


template <typename T>
	requires std::totally_ordered<T>
struct TreeNode {
	T val;
	TreeNode *left;
	TreeNode *right;
	constexpr TreeNode(T x) : val(x), left(NULL), right(NULL) {}	
};

template <typename T>
auto inorderTraversal(TreeNode<T>* root) {
	std::vector<T> result;
	std::stack < TreeNode<T> *> st;
	while (root) {
		st.push(root);
		root = root->left;
	}
	while (!st.empty()) {
		auto top = st.top();
		st.pop();
		result.push_back(top->val);
		root = top->right;
		while (root) {
			st.push(root);
			root = root->left;
		}
	}
	return result;
}

template <typename T>
auto preorderTraversal(TreeNode<T>* root) {
	std::vector<T> ans  { };
	if (root) {
		std::stack<TreeNode<T>*> st { };
		st.push(root);

		while (!st.empty()) {
			auto newnode = st.top();
			st.pop();
			ans.push_back(newnode->val);
			if (newnode->right) st.push(newnode->right);
			if (newnode->left) st.push(newnode->left);
		}
	}

	return ans;
}

std::vector<int> postorderTraversalUsingReverse(TreeNode<int>*A) {
	std::vector<int> ans;
	if (A) {
		std::stack<TreeNode<int>*> st;
		st.push(A);
		while (!st.empty()) {
			TreeNode<int>*top = st.top();
			st.pop();
			ans.push_back(top->val);
			if (top->left) st.push(top->left);
			if (top->right) st.push(top->right);
		}
	}
	std::reverse(ans.begin(), ans.end());
	return ans;
}

template <typename T>
auto postorderTraversal(TreeNode<T>* root) {
	std::vector<T> ans;
	std::stack<TreeNode<T>*> st;

	while (root) {
		st.push(root);
		root = root->left;
	}

	while (!st.empty()) {
		auto top = st.top();
		if (top->right != nullptr) {
			root = top->right;
			while (root) {
				st.push(root);
				root = root->left;
			}
		}
		else {
			st.pop();
			ans.push_back(top->val);
			while (!st.empty() && st.top()->right == top) {
				top = st.top();
				st.pop();
				ans.push_back(top->val);
			}
		}
	}

	return ans;
}

int main()
{
	TreeNode<int>* root = new TreeNode<int>(8);
	root->left = new TreeNode<int>(6);
	root->left->left = new TreeNode<int>(4);
	root->left->right = new TreeNode<int>(7);
	root->right = new TreeNode<int>(12);
	root->right->left = new TreeNode<int>(10);
	root->right->right = new TreeNode<int>(14);

	std::cout << "inorder: " << inorderTraversal<int>(root) << std::endl;
	std::cout << "postorder using reverse: " << postorderTraversalUsingReverse(root) << std::endl;
	std::cout << "postorder: " << postorderTraversal(root) << std::endl;
	std::cout << "preorder: " << preorderTraversal(root) << std::endl;

    return 0;
}

