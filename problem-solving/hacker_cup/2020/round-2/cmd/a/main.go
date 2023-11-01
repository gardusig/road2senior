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
	N  int
	K  int
	S  []int
	As int
	Bs int
	Cs int
	Ds int
	X  []int
	Ax int
	Bx int
	Cx int
	Dx int
	Y  []int
	Ay int
	By int
	Cy int
	Dy int
}

func readTestCaseInputData(input *TestCaseInputData) {
	if _, err := fmt.Scan(&input.N, &input.K); err != nil {
		panic(err)
	}
	input.S = make([]int, input.K)
	for i := 0; i < input.K; i++ {
		if _, err := fmt.Scan(&input.S[i]); err != nil {
			panic(err)
		}
	}
	if _, err := fmt.Scan(&input.As, &input.Bs, &input.Cs, &input.Ds); err != nil {
		panic(err)
	}
	input.X = make([]int, input.K)
	for i := 0; i < input.K; i++ {
		if _, err := fmt.Scan(&input.X[i]); err != nil {
			panic(err)
		}
	}
	if _, err := fmt.Scan(&input.Ax, &input.Bx, &input.Cx, &input.Dx); err != nil {
		panic(err)
	}
	input.Y = make([]int, input.K)
	for i := 0; i < input.K; i++ {
		if _, err := fmt.Scan(&input.Y[i]); err != nil {
			panic(err)
		}
	}
	if _, err := fmt.Scan(&input.Ay, &input.By, &input.Cy, &input.Dy); err != nil {
		panic(err)
	}
}

func parseTestCaseInputData(input *TestCaseInputData) ([]int, []int, []int) {
	S := make([]int, input.N)
	X := make([]int, input.N)
	Y := make([]int, input.N)
	for i := 0; i < input.K; i++ {
		S[i] = input.S[i]
		X[i] = input.X[i]
		Y[i] = input.Y[i]
	}
	for i := input.K; i < input.N; i++ {
		S[i] = ((input.As * S[i-2]) + (input.Bs * S[i-1]) + input.Cs) % input.Ds
		X[i] = ((input.Ax * X[i-2]) + (input.Bx * X[i-1]) + input.Cx) % input.Dx
		Y[i] = ((input.Ay * Y[i-2]) + (input.By * Y[i-1]) + input.Cy) % input.Dy
	}
	return S, X, Y
}

func solveTestCase(input *TestCaseInputData) string {
	S, X, Y := parseTestCaseInputData(input)
	needToAdd := 0
	needToRemove := 0
	total := 0
	minimumRequired := 0
	maximumAllowed := 0
	for i := 0; i < input.N; i++ {
		total += S[i]
		minimumRequired += X[i]
		maximumAllowed += X[i] + Y[i]
		if S[i] < X[i] {
			needToAdd += X[i] - S[i]
		}
		if S[i] > (X[i] + Y[i]) {
			needToRemove += S[i] - (X[i] + Y[i])
		}
	}
	if (total < minimumRequired) || (total > maximumAllowed) {
		return fmt.Sprint(-1)
	}
	answer := max(needToAdd, needToRemove)
	return fmt.Sprint(answer)
}
