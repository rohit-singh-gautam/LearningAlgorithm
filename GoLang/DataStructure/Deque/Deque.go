package main

import "fmt"

type Deque struct {
	store      []interface{}
	size       int
	firstIndex int
}

func NewDeque() *Deque {
	var dq Deque
	dq.firstIndex = 0
	dq.size = 0
	return &dq
}

type CommandId int

const (
	PUSH_BACK CommandId = iota
	POP_BACK
	PUSH_FRONT
	POP_FRONT
	CLEAR
)

type Command struct {
	ID    CommandId
	size  int
	front int
	back  int
}

func (dq *Deque) Size() int {
	return dq.size
}

func (dq *Deque) IsEmpty() bool {
	return dq.size == 0
}

func (dq *Deque) Capacity() int {
	return len(dq.store)
}

func (dq *Deque) ResizeIfRequired() {
	if dq.size < dq.Capacity() {
		return
	}
	newSize := dq.size * 2
	if newSize == 0 {
		newSize = 1
	}

	newstore := make([]interface{}, newSize)
	for index := 0; index < dq.size; index++ {
		newstore[index] = dq.store[(dq.firstIndex+index)%dq.size]
	}
	dq.store = newstore
	dq.firstIndex = 0
}

func (dq *Deque) PushBack(value interface{}) {
	dq.ResizeIfRequired()
	dq.store[(dq.firstIndex+dq.size)%dq.Capacity()] = value
	dq.size++
}

func (dq *Deque) PushFront(value interface{}) {
	dq.ResizeIfRequired()
	dq.firstIndex = (dq.firstIndex + dq.Capacity() - 1) % dq.Capacity()
	dq.store[dq.firstIndex] = value
	dq.size++
}

func (dq *Deque) PopBack() {
	if dq.size == 0 {
		panic("Deque is empty")
	}
	dq.size--
}

func (dq *Deque) PopFront() {
	if dq.size == 0 {
		panic("Deque is empty")
	}
	dq.size--
	dq.firstIndex = (dq.firstIndex + 1) % dq.Capacity()
}

func (dq *Deque) Front() interface{} {
	if dq.size == 0 {
		panic("Deque is empty")
	}
	return dq.store[dq.firstIndex]
}

func (dq *Deque) Back() interface{} {
	if dq.size == 0 {
		panic("Deque is empty")
	}
	return dq.store[(dq.firstIndex+dq.size-1)%dq.Capacity()]
}

func (dq *Deque) Clear() {
	dq.firstIndex = 0
	dq.size = 0
}

func (dq *Deque) ExecuteCommand(cmd Command) bool {
	switch cmd.ID {
	case PUSH_BACK:
		dq.PushBack(cmd.back)

	case POP_BACK:
		dq.PopBack()

	case PUSH_FRONT:
		dq.PushFront(cmd.front)

	case POP_FRONT:
		dq.PopFront()

	case CLEAR:
		dq.Clear()

	default:
		panic("Bad command")
	}

	if cmd.size != dq.size {
		fmt.Printf("Deque Size does not match expected: %d, got: %d\n", cmd.size, dq.Size())
		return false
	}

	if dq.size != 0 {
		if cmd.front != dq.Front() {
			fmt.Printf("Deque Front does not match expected: %d, got: %d ", cmd.front, dq.Front())
			return false
		}
		if cmd.back != dq.Back() {
			fmt.Printf("Deque Back does not match expected: %d, got: %d ", cmd.front, dq.Back())
			return false
		}
	}
	return true
}

func ExecuteTestCommand(test []Command) bool {
	dq := NewDeque()
	for commandIndex, cmd := range test {
		if !dq.ExecuteCommand(cmd) {
			fmt.Printf("Command failed: %d\n", commandIndex)
			return false
		}
	}
	return true
}

func main() {
	testlist := [][]Command{
		{
			{PUSH_BACK, 1, 10, 10},
			{PUSH_FRONT, 2, 20, 10},
			{PUSH_BACK, 3, 20, 30},
			{PUSH_FRONT, 4, 10, 30},
			{CLEAR, 0, 0, 0},
		},
		{
			{PUSH_BACK, 1, 20, 20},
			{PUSH_BACK, 2, 20, 5},
			{POP_FRONT, 1, 5, 5},
			{PUSH_BACK, 2, 5, 10},
			{PUSH_BACK, 3, 5, 15},
			{POP_BACK, 2, 5, 10},
			{PUSH_BACK, 3, 5, 20},
			{PUSH_FRONT, 4, 5, 20},
			{PUSH_FRONT, 5, 10, 20},
			{PUSH_BACK, 6, 10, 15},
			{POP_FRONT, 5, 5, 15},
			{POP_FRONT, 4, 5, 15},
			{POP_FRONT, 3, 10, 15},
			{POP_FRONT, 2, 20, 15},
		},
		{
			{PUSH_BACK, 1, 1, 1},
			{PUSH_BACK, 2, 1, 2},
			{PUSH_BACK, 3, 1, 3},
			{POP_FRONT, 2, 2, 3},
			{CLEAR, 0, 0, 0},
			{PUSH_BACK, 1, 1, 1},
			{PUSH_BACK, 2, 1, 2},
			{PUSH_BACK, 3, 1, 3},
			{POP_FRONT, 2, 2, 3},
		},
		{
			{PUSH_BACK, 1, 1, 1},
			{PUSH_BACK, 2, 1, 2},
			{PUSH_BACK, 3, 1, 3},
			{PUSH_BACK, 4, 1, 5},
			{POP_FRONT, 3, 2, 5},
			{CLEAR, 0, 0, 0},
		},
		{
			{PUSH_BACK, 1, 20, 20},
			{PUSH_BACK, 2, 20, 5},
			{POP_FRONT, 1, 5, 5},
			{POP_FRONT, 0, 0, 0},
			{PUSH_BACK, 1, 10, 10},
			{PUSH_BACK, 2, 10, 15},
			{POP_FRONT, 1, 15, 15},
			{CLEAR, 0, 0, 0},
			{PUSH_BACK, 1, 20, 20},
			{PUSH_BACK, 2, 20, 5},
			{PUSH_BACK, 3, 20, 10},
			{PUSH_BACK, 4, 20, 15},
			{POP_FRONT, 3, 5, 15},
			{POP_FRONT, 2, 10, 15},
			{POP_FRONT, 1, 15, 15},
			{POP_FRONT, 0, 0, 0},
		},
		{
			{PUSH_BACK, 1, 1, 1},
			{PUSH_BACK, 2, 1, 2},
			{PUSH_BACK, 3, 1, 3},
			{PUSH_BACK, 4, 1, 4},
			{PUSH_BACK, 5, 1, 5},
			{POP_FRONT, 4, 2, 5},
			{CLEAR, 0, 0, 0},
		},
	}

	for index, test := range testlist {
		fmt.Printf("Test %d\n", index)
		if !ExecuteTestCommand(test) {
			fmt.Printf("Test %d failed\n", index)
		}
	}
}
