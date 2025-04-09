package main

import "fmt"

type Stack struct {
	store    []interface{}
	topIndex int
}

type StackCommandId int

const (
	PUSH StackCommandId = iota
	POP
	CLEAR
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

func (st *Stack) ExecuteCommand(cmd StackCommand) bool {
	switch cmd.command {
	case PUSH:
		st.Push(cmd.value)

	case POP:
		st.Pop()

	case CLEAR:
		st.Clear()
	}

	if cmd.size != st.Size() {
		fmt.Printf("Stack Size does not match expected: %d, got: %d\n", cmd.size, st.Size())
		return false
	}

	if cmd.size != 0 {
		if cmd.value != st.Top() {
			fmt.Printf("Stack Top does not match expected: %d, got: %d ", cmd.value, st.Top())
			return false
		}
	}
	return true
}

func RunTestCommands(test []StackCommand) bool {
	st := NewStack()
	for commandIndex, cmd := range test {
		if !st.ExecuteCommand(cmd) {
			fmt.Printf("Command %d failed\n", commandIndex)
			return false
		}
	}
	return true
}

func main() {
	testlist := [][]StackCommand{
		{
			{PUSH, 1, 1},
			{PUSH, 2, 2},
			{PUSH, 3, 3},
			{POP, 2, 2},
			{CLEAR, 0, 0},
		},
		{
			{PUSH, 1, 3},
			{PUSH, 2, 1},
			{PUSH, 3, 2},
			{PUSH, 4, 3},
			{PUSH, 5, 8},
			{POP, 4, 3},
			{CLEAR, 0, 0},
		},
		{
			{PUSH, 1, 10},
			{PUSH, 2, 20},
			{POP, 1, 10},
			{PUSH, 2, 30},
		},
		{
			{PUSH, 1, 10},
			{PUSH, 2, 20},
			{PUSH, 3, 40},
			{PUSH, 4, 80},
			{PUSH, 5, 20},
			{PUSH, 6, 100},
			{POP, 5, 20},
			{PUSH, 6, 30},
			{CLEAR, 0, 0},
		},
	}

	for index, test := range testlist {
		fmt.Printf("Runnig Test: %d\n", index+1)
		if !RunTestCommands(test) {
			fmt.Printf("Test %d failed\n", index+1)
		}
	}
}
