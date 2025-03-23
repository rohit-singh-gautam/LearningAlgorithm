package main

import (
	"fmt"

	"github.com/golang-collections/collections/stack"
)

type BinaryNode struct {
	value int
	left  *BinaryNode
	right *BinaryNode
}

func (root *BinaryNode) InorderRecursiveHelper(result []int) []int {
	if root == nil {
		return result
	}
	result = root.left.InorderRecursiveHelper(result)
	result = append(result, root.value)
	result = root.right.InorderRecursiveHelper(result)
	return result
}

func (root *BinaryNode) InorderRecursive() (result []int) {
	return root.InorderRecursiveHelper(result)
}

func (root *BinaryNode) InorderIterative() (result []int) {
	st := stack.New()
	for st.Len() != 0 || root != nil {
		if root != nil {
			st.Push(root)
			root = root.left
		} else {
			top := st.Pop().(*BinaryNode)
			result = append(result, top.value)
			root = top.right
		}
	}
	return
}

func (root *BinaryNode) PreorderRecursiveHelper(result []int) []int {
	if root == nil {
		return result
	}
	result = append(result, root.value)
	result = root.left.PreorderRecursiveHelper(result)
	result = root.right.PreorderRecursiveHelper(result)
	return result
}

func (root *BinaryNode) PreorderRecursive() (result []int) {
	return root.PreorderRecursiveHelper(result)
}

func (root *BinaryNode) PreorderIterative() (result []int) {
	st := stack.New()
	for st.Len() != 0 || root != nil {
		if root != nil {
			result = append(result, root.value)
			st.Push(root)
			root = root.left
		} else {
			top := st.Pop().(*BinaryNode)
			root = top.right
		}
	}
	return
}

func (root *BinaryNode) PostorderRecursiveHelper(result []int) []int {
	if root == nil {
		return result
	}
	result = root.left.PostorderRecursiveHelper(result)
	result = root.right.PostorderRecursiveHelper(result)
	result = append(result, root.value)
	return result
}
func (root *BinaryNode) PostorderRecursive() (result []int) {
	return root.PostorderRecursiveHelper(result)
}

func (root *BinaryNode) PostorderIterative() (result []int) {
	st := stack.New()
	for st.Len() != 0 || root != nil {
		if root != nil {
			st.Push(root)
			root = root.left
		} else {
			top := st.Peek().(*BinaryNode)
			if top.right == nil {
				result = append(result, top.value)
				prev := top
				st.Pop()
				for st.Len() != 0 {
					top = st.Pop().(*BinaryNode)
					if top.right == nil || top.right == prev {
						result = append(result, top.value)
						prev = top
					} else {
						st.Push(top)
						root = top.right
						break
					}
				}
			} else {
				st.Push(top)
				root = top.right
			}
		}
	}
	return
}

func (root *BinaryNode) FreeRecursive() {
	if root == nil {
		return
	}
	root.left.FreeRecursive()
	root.right.FreeRecursive()
	root.left = nil
	root.right = nil
}

// -1 will represent null
func CreateBinaryTreeHelper(value []int, index *int) *BinaryNode {
	if *index == len(value) {
		return nil
	}

	currentvalue := value[*index]
	*index += 1
	if currentvalue != -1 {
		root := new(BinaryNode)
		root.value = currentvalue
		root.left = CreateBinaryTreeHelper(value, index)
		root.right = CreateBinaryTreeHelper(value, index)
		return root
	}
	return nil
}

func CreateBinaryTree(value []int) *BinaryNode {
	var index int
	return CreateBinaryTreeHelper(value, &index)
}

func CompareSlices(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}
	for index, value := range a {
		if value != b[index] {
			return false
		}
	}
	return true
}

func test(value []int) {
	root := CreateBinaryTree(value)
	preorderRecursiveResult := root.PreorderRecursive()
	fmt.Println("Preorder Recursive: ", preorderRecursiveResult)
	inorderRecursiveResult := root.InorderRecursive()
	fmt.Println("Inorder Recursive: ", inorderRecursiveResult)
	postorderRecursiveResult := root.PostorderRecursive()
	fmt.Println("Postorder Recursive: ", postorderRecursiveResult)

	preorderIterativeResult := root.PreorderIterative()
	fmt.Println("Preorder Iterative: ", preorderIterativeResult)
	inorderIterativeResult := root.InorderIterative()
	fmt.Println("Inorder Iterative: ", inorderIterativeResult)
	postorderIterativeResult := root.PostorderIterative()
	fmt.Println("Postorder Iterative: ", postorderIterativeResult)

	if !CompareSlices(preorderRecursiveResult, preorderIterativeResult) {
		fmt.Println("Test Failed: Preorder Recursive and Preorder Iterative are not same")
	}

	if !CompareSlices(inorderRecursiveResult, inorderIterativeResult) {
		fmt.Println("Test Failed: Inorder Recursive and Inorder Iterative are not same")
	}

	if !CompareSlices(postorderRecursiveResult, postorderIterativeResult) {
		fmt.Println("Test Failed: Postorder Recursive and Postorder Iterative are not same")
	}
}

func main() {
	testlist := [][]int{
		{20, -1, -1, 40}, // 40 must be ignored
		{50},
		{50, 40, -1, -1, 60},
		{50, 40},
		{50, 40, 30},
		{50, 30, 20, -1, -1, 40, -1, 45, -1, -1, 80, 70, -1, -1, 90, -1, -1},
		{50, 30, 20, -1, -1, 40, -1, 45, -1, -1, 80, 70, -1, -1, 90}, // -1 at the end not required
		{100, 50, 25, 12, -1, -1, 37, -1, -1, 75, 62, -1, -1, 87, -1, -1, 150, 125, 112, -1, -1, 137, -1, -1, 175, 162, -1, -1, 187},
	}

	for index, testentry := range testlist {
		fmt.Println("Test: ", index)
		test(testentry)
	}
}
