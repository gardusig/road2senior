package main

import (
	"container/heap"
	"fmt"
)

func main() {
	var testCases int
	if _, err := fmt.Scan(&testCases); err != nil {
		panic(err)
	}
	testCasesInputData := make([]TestCaseInputData, testCases)
	for testCase := 0; testCase < testCases; testCase++ {
		readTestCaseInputData(&testCasesInputData[testCase])
	}
	testCaseOutputList := make([]chan string, testCases)
	for testCase := 0; testCase < testCases; testCase++ {
		testCaseOutputList[testCase] = make(chan string, 1)
		go solveTestCaseAsync(&testCasesInputData[testCase], testCaseOutputList[testCase])
	}
	for testCase := 0; testCase < testCases; testCase++ {
		fmt.Printf("Case #%d: %s\n", testCase+1, <-testCaseOutputList[testCase])
	}
}

func solveTestCaseAsync(input *TestCaseInputData, output chan string) {
	output <- solveTestCase(input)
}

type TestCaseInputData struct {
	N int
	M int
	P []int
	C []int
}

func readTestCaseInputData(input *TestCaseInputData) {
	var A, B int
	if _, err := fmt.Scan(&input.N, &input.M, &A, &B); err != nil {
		panic(err)
	}
	input.P = make([]int, input.N)
	for i := 1; i < input.N; i++ {
		if _, err := fmt.Scan(&input.P[i]); err != nil {
			panic(err)
		}
	}
	input.C = make([]int, input.M)
	for i := 0; i < input.M; i++ {
		input.C[i] = (A*i + B) % input.N
	}
}

type MaxHeap []int

func (h MaxHeap) Len() int            { return len(h) }
func (h MaxHeap) Less(i, j int) bool  { return h[i] > h[j] }
func (h MaxHeap) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x interface{}) { *h = append(*h, x.(int)) }
func (h *MaxHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func merge(x *MaxHeap, y *MaxHeap) *MaxHeap {
	if x.Len() < y.Len() {
		return merge(y, x)
	}
	for y.Len() > 0 {
		poppedElement := heap.Pop(y).(int)
		heap.Push(x, poppedElement)
	}
	return x
}

func dfs(node int, parent int, graph [][]int, customersAtSubtree []int) (int, *MaxHeap) {
	answer := 0
	availableCandies := &MaxHeap{}
	for _, nxt := range graph[node] {
		if nxt == parent {
			continue
		}
		childAnswer, childAvailableCandies := dfs(nxt, node, graph, customersAtSubtree)
		answer += childAnswer
		availableCandies = merge(availableCandies, childAvailableCandies)
	}
	heap.Push(availableCandies, node)
	for customersAtSubtree[node] > 0 && availableCandies.Len() > 0 {
		highestCandy := heap.Pop(availableCandies).(int)
		answer += highestCandy
		customersAtSubtree[node]--
	}
	return answer, availableCandies
}

func solveTestCase(input *TestCaseInputData) string {
	graph := make([][]int, input.N)
	for i := 0; i < input.N; i++ {
		graph[i] = make([]int, 0)
	}
	for i := 1; i < input.N; i++ {
		j := input.P[i]
		graph[i] = append(graph[i], j)
		graph[j] = append(graph[j], i)
	}
	customersAtSubtree := make([]int, input.N)
	for i := 0; i < input.M; i++ {
		customersAtSubtree[input.C[i]]++
	}
	answer, _ := dfs(0, -1, graph, customersAtSubtree)
	return fmt.Sprint(answer)
}
