package main

import "fmt"

type Stack struct {
	store    []interface{}
	topIndex int
}

func NewStack() *Stack {
	var st Stack
	st.topIndex = 0
	return &st
}

func (st *Stack) Push(value interface{}) {
	if len(st.store) > st.topIndex {
		st.store[st.topIndex] = value
	} else {
		st.store = append(st.store, value)
	}
	st.topIndex++
}

func (st *Stack) Pop() {
	if st.topIndex == 0 {
		panic("Stack empty")
	}
	st.topIndex--
}

func (st *Stack) Top() interface{} {
	if st.topIndex == 0 {
		panic("Stack empty")
	}
	return st.store[st.topIndex-1]
}

func (st *Stack) IsEmpty() bool {
	return st.topIndex == 0
}

func (st *Stack) Size() int {
	return st.topIndex
}

func main() {
	st := NewStack()
	st.Push(10)
	st.Push(20)
	st.Pop()
	st.Push(30)
	if st.Top() != 30 {
		panic("Test failed")
	}

	fmt.Println("Test Passed")
}
