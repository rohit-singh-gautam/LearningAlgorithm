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

func (root *BinaryNode) InorderRecursive() {
	if root == nil {
		return
	}
	root.left.InorderRecursive()
	fmt.Print(root.value, " ")
	root.right.InorderRecursive()
}

func (root *BinaryNode) InorderIterative() {
	st := stack.New()
	for st.Len() != 0 || root != nil {
		if root != nil {
			st.Push(root)
			root = root.left
		} else {
			top := st.Pop().(*BinaryNode)
			fmt.Print(top.value, " ")
			root = top.right
		}
	}
}

func (root *BinaryNode) PreorderRecursive() {
	if root == nil {
		return
	}
	fmt.Print(root.value, " ")
	root.left.PreorderRecursive()
	root.right.PreorderRecursive()
}

func (root *BinaryNode) PostorderRecursive() {
	if root == nil {
		return
	}
	root.left.PostorderRecursive()
	root.right.PostorderRecursive()
	fmt.Print(root.value, " ")
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

func test(value []int) {
	root := CreateBinaryTree(value)
	fmt.Print("Preorder Recursive: ")
	root.PreorderRecursive()
	fmt.Println()
	fmt.Print("Inorder Recursive: ")
	root.InorderRecursive()
	fmt.Println()
	fmt.Print("Postorder Recursive: ")
	root.PostorderRecursive()
	fmt.Println()

	fmt.Print("Inorder Iterative: ")
	root.InorderIterative()
	fmt.Println()
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
