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
	pushBack CommandId = iota
	popBack
	pushFront
	popFront
	verify
	clear
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

func (dq *Deque) ExecuteCommand(cmd Command) {
	switch cmd.ID {
	case pushBack:
		dq.PushBack(cmd.back)

	case popBack:
		dq.PopBack()

	case pushFront:
		dq.PushFront(cmd.front)

	case popFront:
		dq.PopFront()

	case verify:
		// Do nothing

	case clear:
		dq.Clear()

	default:
		panic("Bad command")
	}

	if cmd.size != dq.size {
		panic("Command size mismatch")
	}

	if dq.size != 0 {
		if cmd.front != dq.Front() {
			panic("Front mismatch")
		}
		if cmd.back != dq.Back() {
			panic("Back mismatch")
		}
	}
}

func ExecuteTestCommand(test []Command) {
	dq := NewDeque()
	for _, cmd := range test {
		dq.ExecuteCommand(cmd)
	}
}

func main() {
	testlist := [][]Command{
		{
			{pushBack, 1, 10, 10},
			{pushFront, 2, 20, 10},
			{pushBack, 3, 20, 30},
			{popFront, 2, 10, 30},
			{clear, 0, 0, 0},
		},
	}

	for index, test := range testlist {
		fmt.Printf("Test %d\n", index)
		ExecuteTestCommand(test)
	}
}
