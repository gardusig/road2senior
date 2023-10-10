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
	S string
	Q int
	B []int
}

func readTestCaseInputData(input *TestCaseInputData) {
	if _, err := fmt.Scan(&input.N); err != nil {
		panic(err)
	}
	if _, err := fmt.Scan(&input.S); err != nil {
		panic(err)
	}
	if _, err := fmt.Scan(&input.Q); err != nil {
		panic(err)
	}
	input.B = make([]int, input.Q)
	for i := 0; i < input.Q; i++ {
		if _, err := fmt.Scan(&input.B[i]); err != nil {
			panic(err)
		}
	}
}

func solveTestCase(input *TestCaseInputData) string {
	current := 0
	isPressRequiredToSolve := countNeededPresses(input.N, input.S)
	for idx := 1; idx <= input.N; idx += 1 {
		if isPressRequiredToSolve[idx] {
			current += 1
		}
	}
	total := 0
	for _, b := range input.B {
		if isPressRequiredToSolve[b] {
			current--
		} else {
			current++
		}
		isPressRequiredToSolve[b] = !isPressRequiredToSolve[b]
		total += current
	}
	return fmt.Sprint(total)
}

func countNeededPresses(N int, S string) []bool {
	totalPressList := make([]int, N+1)
	isPressRequiredToSolve := make([]bool, N+1)
	for i := 1; i <= N; i++ {
		if S[i-1] == '1' {
			totalPressList[i] += 1
		}
		if (totalPressList[i] & 1) == 0 {
			continue
		}
		isPressRequiredToSolve[i] = true
		for j := i; j <= N; j += i {
			totalPressList[j] += 1
		}
	}
	return isPressRequiredToSolve
}
