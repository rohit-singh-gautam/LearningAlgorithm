package main

import "fmt"

type CommandID int

const (
	ENQUEUE CommandID = iota
	DEQUEUE
	CLEAR
)

type TestCommand struct {
	ID    CommandID
	size  int
	front int
	back  int
}

type Queue struct {
	store      []interface{}
	firstIndex int
	size       int
}

func NewQueue() *Queue {
	var q Queue
	q.firstIndex = 0
	q.size = 0
	return &q
}

func (q *Queue) Capacity() int {
	return len(q.store)
}

func (q *Queue) Size() int {
	return q.size
}

func (q *Queue) Front() interface{} {
	if q.size == 0 {
		panic("Trying to get front from empty queue")
	}
	return q.store[q.firstIndex]
}

func (q *Queue) Back() interface{} {
	if q.size == 0 {
		panic("Trying to get back from empty queue")
	}
	return q.store[(q.firstIndex+q.size-1)%q.Capacity()]
}

func (q *Queue) ResizeIfRequired() {
	if q.size < q.Capacity() {
		return
	}

	newCapacity := q.Capacity() * 2
	if newCapacity == 0 {
		q.store = make([]interface{}, 1)
		return
	}

	newStore := make([]interface{}, newCapacity)

	for index := 0; index < q.Capacity(); index++ {
		newStore[index] = q.store[(q.firstIndex+index)%q.Capacity()]
	}

	q.store = newStore
	q.firstIndex = 0
}

func (q *Queue) Enqueue(value interface{}) {
	q.ResizeIfRequired()
	q.store[(q.firstIndex+q.size)%q.Capacity()] = value
	q.size++
}

func (q *Queue) Dequeue() {
	if q.size == 0 {
		panic("Trying to get dequeue empty queue")
	}
	q.firstIndex = (q.firstIndex + 1) % q.Capacity()
	q.size--
}

func (q *Queue) Clear() {
	q.size = 0
}

func (q *Queue) ExecuteCommand(cmd TestCommand) bool {
	switch cmd.ID {
	case ENQUEUE:
		q.Enqueue(cmd.back)

	case DEQUEUE:
		q.Dequeue()

	case CLEAR:
		q.Clear()
	}

	if q.size != cmd.size {
		fmt.Printf("Queue size mismatch expected: %d, got: %d\n", cmd.size, q.size)
		return false
	}

	if q.size != 0 {
		if cmd.front != q.Front() {
			fmt.Printf("Queue Front does not match expected: %d, got: %d\n", cmd.front, q.Front())
			return false
		}
		if cmd.back != q.Back() {
			fmt.Printf("Queue Back does not match expected: %d, got: %d\n", cmd.front, q.Back())
			return false
		}
	}
	return true
}

func ExecuteTestCommand(test []TestCommand) bool {
	q := NewQueue()
	for commandIndex, cmd := range test {
		if !q.ExecuteCommand(cmd) {
			fmt.Printf("Test command %d failed\n", commandIndex)
			return false
		}
	}
	return true
}

func main() {
	testlist := [][]TestCommand{
		{
			{ENQUEUE, 1, 1, 1},
			{ENQUEUE, 2, 1, 2},
			{ENQUEUE, 3, 1, 3},
			{DEQUEUE, 2, 2, 3},
			{CLEAR, 0, 0, 0},
		},
		{
			{ENQUEUE, 1, 1, 1},
			{ENQUEUE, 2, 1, 2},
			{ENQUEUE, 3, 1, 3},
			{ENQUEUE, 4, 1, 5},
			{DEQUEUE, 3, 2, 5},
			{CLEAR, 0, 0, 0},
		},
		{
			{ENQUEUE, 1, 20, 20},
			{ENQUEUE, 2, 20, 5},
			{DEQUEUE, 1, 5, 5},
			{DEQUEUE, 0, 0, 0},
			{ENQUEUE, 1, 10, 10},
			{ENQUEUE, 2, 10, 15},
			{DEQUEUE, 1, 15, 15},
			{CLEAR, 0, 0, 0},
			{ENQUEUE, 1, 20, 20},
			{ENQUEUE, 2, 20, 5},
			{ENQUEUE, 3, 20, 10},
			{ENQUEUE, 4, 20, 15},
			{DEQUEUE, 3, 5, 15},
			{DEQUEUE, 2, 10, 15},
			{DEQUEUE, 1, 15, 15},
			{DEQUEUE, 0, 0, 0},
		},
		{
			{ENQUEUE, 1, 1, 1},
			{ENQUEUE, 2, 1, 2},
			{ENQUEUE, 3, 1, 3},
			{ENQUEUE, 4, 1, 4},
			{ENQUEUE, 5, 1, 5},
			{DEQUEUE, 4, 2, 5},
			{CLEAR, 0, 0, 0},
		},
	}

	for testIndex, test := range testlist {
		fmt.Printf("Test %d running\n", testIndex)
		if !ExecuteTestCommand(test) {
			panic(fmt.Sprintf("Test %d failed", testIndex))
		}
	}
	fmt.Printf("All test passed\n")
}
