package main

import (
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
	K int
}

func readTestCaseInputData(input *TestCaseInputData) {
	if _, err := fmt.Scan(&input.N, &input.K); err != nil {
		panic(err)
	}
}

func addEdge(from int, to int, cost int, totalEdgeCost *int, edgeCounter *int, edges *string) {
	*totalEdgeCost += cost
	*edgeCounter += 1
	*edges += fmt.Sprintf("\n%d %d %d", from, to, cost)
}

func solveTestCase(input *TestCaseInputData) string {
	totalEdgeCost := 0
	edgeCounter := 1
	edges := fmt.Sprintf("%d %d %d", 1, input.N, input.K)
	if (input.K < 3) || (input.N < 3) {
		return fmt.Sprintf("%d\n%d\n%s", totalEdgeCost, edgeCounter, edges)
	}
	totalEdgeCost -= input.K
	for i := 0; i < min(input.N, input.K)-2; i++ {
		addEdge(
			i+1,
			i+2,
			input.K-i-1,
			&totalEdgeCost, &edgeCounter, &edges,
		)
	}
	addEdge(
		min(input.N, input.K)-1,
		input.N,
		max(1, input.K-input.N+1),
		&totalEdgeCost, &edgeCounter, &edges,
	)
	return fmt.Sprintf("%d\n%d\n%s", totalEdgeCost, edgeCounter, edges)
}
