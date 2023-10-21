package main

import (
	"fmt"
	"math"
	"sort"
)

type TestCaseInputData struct {
	N int
	X []int
}

func solve(N int, X []int) string {
	sort.Ints(X)
	middleFirstTwo := float64(X[0]+X[1]) / 2.0
	middleLastTwo := float64(X[N-2]+X[N-1]) / 2.0
	if N == 5 {
		middleFirstThree := float64(X[0]+X[2]) / 2.0
		middleLastThree := float64(X[2]+X[4]) / 2.0
		return fmt.Sprintf("%.1f", math.Max(
			middleLastTwo-middleFirstThree,
			middleLastThree-middleFirstTwo,
		))
	}
	return fmt.Sprintf("%.1f", middleLastTwo-middleFirstTwo)
}

func solveTestCase(input *TestCaseInputData, output chan string) {
	answer := solve(
		input.N,
		input.X,
	)
	output <- answer
}

func readTestCaseInputData(input *TestCaseInputData) error {
	_, err := fmt.Scan(&input.N)
	if err != nil {
		return err
	}
	input.X = make([]int, input.N)
	for i := 0; i < input.N; i++ {
		_, err = fmt.Scan(&input.X[i])
		if err != nil {
			return err
		}
	}
	return nil
}

func main() {
	var testCases int
	_, err := fmt.Scan(&testCases)
	if err != nil {
		panic(err)
	}
	testCasesInputData := make([]TestCaseInputData, testCases)
	for testCase := 0; testCase < testCases; testCase++ {
		err = readTestCaseInputData(&testCasesInputData[testCase])
		if err != nil {
			panic(err)
		}
	}
	testCaseOutputList := make([]chan string, testCases)
	for testCase := 0; testCase < testCases; testCase++ {
		testCaseOutputList[testCase] = make(chan string, 1)
		solveTestCase(&testCasesInputData[testCase], testCaseOutputList[testCase])
	}
	for testCase := 0; testCase < testCases; testCase++ {
		fmt.Printf("Case #%d: %s\n", testCase+1, <-testCaseOutputList[testCase])
	}
}
