package main

import (
	"fmt"
)

type TestCaseInputData struct {
	N int
	S string
	Q int
	B []int
}

func solve(input *TestCaseInputData) string {
	sumArray := make([]int, input.N+1)
	for _, b := range input.B {
		sumArray[b]++
	}
	answer := 0
	for i := 1; i <= input.N; i++ {
		total := 0
		if input.S[i-1] == '1' {
			total++
		}
		for j := 1; j*j <= i; j++ {
			if i%j != 0 {
				continue
			}
			total += sumArray[j]
			other := i / j
			if other != j {
				total += sumArray[other]
			}
		}
		if (total & 1) > 0 {
			answer++
			sumArray[i]++
		}
	}
	return fmt.Sprint(answer)
}

func solveTestCase(input *TestCaseInputData, output chan string) {
	output <- solve(input)
}

func readTestCaseInputData(input *TestCaseInputData) error {
	if _, err := fmt.Scan(&input.N); err != nil {
		return err
	}
	if _, err := fmt.Scan(&input.S); err != nil {
		return err
	}
	if _, err := fmt.Scan(&input.Q); err != nil {
		return err
	}
	input.B = make([]int, input.Q)
	for i := 0; i < input.Q; i++ {
		if _, err := fmt.Scan(&input.B[i]); err != nil {
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
		go solveTestCase(&testCasesInputData[testCase], testCaseOutputList[testCase])
	}
	for testCase := 0; testCase < testCases; testCase++ {
		fmt.Printf("Case #%d: %s\n", testCase+1, <-testCaseOutputList[testCase])
	}
}
