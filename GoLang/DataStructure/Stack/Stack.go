package main

import "fmt"

type Stack struct {
	store    []interface{}
	topIndex int
}

type StackCommandId int

const (
	push StackCommandId = iota
	pop
	top
	clear
)

type StackCommand struct {
	command StackCommandId
	size    int
	value   int
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

func (st *Stack) Clear() {
	st.topIndex = 0
}

func (st *Stack) ExecuteCommand(cmd StackCommand) {
	switch cmd.command {
	case push:
		st.Push(cmd.value)

	case pop:
		st.Pop()

	case top:
		if cmd.value != st.Top() {
			panic(fmt.Sprintf("Stack Top does not match expected: %d, got: %d ", cmd.value, st.Top().(int)))
		}

	case clear:
		st.Clear()
	}

	if cmd.size != st.Size() {
		panic(fmt.Sprintf("Stack Size does not match expected: %d, got: %d ", cmd.size, st.Size()))
	}
}

func RunTestCommands(test []StackCommand) {
	st := NewStack()
	for _, cmd := range test {
		st.ExecuteCommand(cmd)
	}
}

func main() {
	testlist := [][]StackCommand{
		{
			{push, 1, 10},
			{push, 2, 20},
			{pop, 1, 0},
			{top, 1, 10},
			{push, 2, 30},
			{top, 2, 30},
		},
		{
			{push, 1, 10},
			{push, 2, 20},
			{push, 3, 40},
			{push, 4, 80},
			{push, 5, 20},
			{push, 6, 100},
			{top, 6, 100},
			{pop, 5, 0},
			{push, 6, 30},
			{top, 6, 30},
			{clear, 0, 0},
		},
	}

	for index, test := range testlist {
		fmt.Printf("Runnig Test: %d\n", index+1)
		RunTestCommands(test)
	}
}
