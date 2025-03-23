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
	template <typename T1>
	constexpr TreeNode(T1&& x, TreeNode *left = nullptr, TreeNode *right = nullptr) : val{ std::forward<T>(x) }, left { left }, right { right } {}	
};

template <typename T>
auto InorderIterative(TreeNode<T>* root) {
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
auto PreorderIterative(TreeNode<T>* root) {
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

std::vector<int> PostorderIterativeUsingReverse(TreeNode<int>*A) {
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
auto PostorderIterative(TreeNode<T>* root) {
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

template <typename T>
void PreorderRecursive(TreeNode<T>* root, std::vector<T> &result) {
	if (root) {
		result.push_back(root->val);
		PreorderRecursive(root->left, result);
		PreorderRecursive(root->right, result);
	}
}

template <typename T>
auto PreorderRecursive(TreeNode<T>* root) {
	std::vector<T> result { };
	PreorderRecursive(root, result);
	return result;
}

template <typename T>
void InorderRecursive(TreeNode<T>* root, std::vector<T> &result) {
	if (root) {
		InorderRecursive(root->left, result);
		result.push_back(root->val);
		InorderRecursive(root->right, result);
	}
}

template <typename T>
auto InorderRecursive(TreeNode<T>* root) {
	std::vector<T> result { };
	InorderRecursive(root, result);
	return result;
}

template <typename T>
void PostorderRecursive(TreeNode<T>* root, std::vector<T> &result) {
	if (root) {
		PostorderRecursive(root->left, result);
		PostorderRecursive(root->right, result);
		result.push_back(root->val);
	}
}

template <typename T>
auto PostorderRecursive(TreeNode<T>* root) {
	std::vector<T> result { };
	PostorderRecursive(root, result);
	return result;
}

template <typename T, T nullValue>
TreeNode<T> *CreateBinaryTreeHelper(const std::vector<T> &values, size_t &index) {
	if (index == values.size()) {
		return nullptr;
	}

	auto currentvalue = values[index++];
	if (currentvalue != nullValue) {
		auto left = CreateBinaryTreeHelper<T, nullValue>(values, index);
		auto right = CreateBinaryTreeHelper<T, nullValue>(values, index);
		auto root = new TreeNode<T>(currentvalue, left, right);
		return root;
	}
	return nullptr;
}

template <typename T>
void FreeRecursive(TreeNode<T> *root) {
	if (root) {
		FreeRecursive(root->left);
		FreeRecursive(root->right);
		delete root;
	}
}

template <typename T, T nullValue>
bool TestBinaryTree(const std::vector<T> &values) {
	size_t index = 0;
	auto root = CreateBinaryTreeHelper<T, nullValue>(values, index);
	const auto preorderRecursive = PreorderRecursive(root);
	const auto inorderRecursive = InorderRecursive(root);
	const auto postorderRecursive = PostorderRecursive(root);
	const auto preorderIterative = PreorderIterative(root);
	const auto inorderIterative = InorderIterative(root);
	const auto postorderIterative = PostorderIterative(root);
	const auto postorderIterativeUsingReverse = PostorderIterativeUsingReverse(root);
	FreeRecursive(root);
	std::cout << "Preorder Recursive: " << preorderRecursive << std::endl;
	std::cout << "Inorder Recursive: " << inorderRecursive << std::endl;
	std::cout << "Postorder Recursive: " << postorderRecursive << std::endl;
	std::cout << "Preorder Iterative: " << preorderIterative << std::endl;
	std::cout << "Inorder Iterative: " << inorderIterative << std::endl;
	std::cout << "Postorder Iterative: " << postorderIterative << std::endl;
	std::cout << "Postorder Recursive Using Recursive: " << postorderIterativeUsingReverse << std::endl;

	if (preorderRecursive != preorderIterative) {
		std::cout << "Preorder mismatch\n";
		return false;
	}
	if (inorderRecursive != inorderIterative) {
		std::cout << "Inorder mismatch\n";
		return false;
	}
	if (postorderRecursive != postorderIterative) {
		std::cout << "Postorder mismatch\n";
		return false;
	}
	if (postorderRecursive != postorderIterativeUsingReverse) {
		std::cout << "Postorder using reverse mismatch\n";
		return false;
	}
	return true;
}

int main()
{
	std::vector<std::vector<int>> testlist {
		{20, -1, -1, 40}, // 40 must be ignored
		{50},
		{50, 40, -1, -1, 60},
		{50, 40},
		{50, 40, 30},
		{50, 30, 20, -1, -1, 40, -1, 45, -1, -1, 80, 70, -1, -1, 90, -1, -1},
		{50, 30, 20, -1, -1, 40, -1, 45, -1, -1, 80, 70, -1, -1, 90}, // -1 at the end not required
		{100, 50, 25, 12, -1, -1, 37, -1, -1, 75, 62, -1, -1, 87, -1, -1, 150, 125, 112, -1, -1, 137, -1, -1, 175, 162, -1, -1, 187},
		{100, 50, 25, 12, -1, -1, 37, -1, -1, 75, 62, -1, -1, 87, -1, -1, 150, 125, 112, -1, -1, 137, -1, -1, 175, 162, -1, -1, 187, -1}, // -1 at the end not required
	};

	for(const auto &test: testlist) {
		std::cout << "Test: " << test << std::endl;
		auto ret = TestBinaryTree<int, -1>(test);
		if (!ret) {
			std::cout << "Test failed\n";
			break;
		}
	}

    return 0;
}

