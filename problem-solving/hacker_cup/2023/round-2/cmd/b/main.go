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
	A []int
	B []int
}

func readTestCaseInputData(input *TestCaseInputData) {
	if _, err := fmt.Scan(&input.N); err != nil {
		panic(err)
	}
	input.A = make([]int, input.N)
	for i := 0; i < input.N; i++ {
		if _, err := fmt.Scan(&input.A[i]); err != nil {
			panic(err)
		}
	}
	input.B = make([]int, input.N)
	for i := 0; i < input.N; i++ {
		if _, err := fmt.Scan(&input.B[i]); err != nil {
			panic(err)
		}
	}
}

func isValid(L int, R int, N int, v []int) bool {
	for i := 0; i < (N >> 1); i++ {
		if v[L+i] >= v[R+i] {
			return false
		}
	}
	for i := (N + 1) >> 1; i < N; i++ {
		if v[L+i] <= v[R+i] {
			return false
		}
	}
	return true
}

func isPalindrome(L int, R int, v []int) bool {
	for L < R {
		if v[L] != v[R] {
			return false
		}
		L++
		R--
	}
	return true
}

func isClearlyInvalid(N int, A []int, B []int) bool {
	elementFrequency := make(map[int]int)
	for i := 0; i < N; i++ {
		elementFrequency[A[i]]++
		elementFrequency[B[i]]++
	}
	hasOddFrequency := false
	for _, value := range elementFrequency {
		if (value & 1) == 1 {
			if hasOddFrequency {
				return true
			}
			hasOddFrequency = true
		}
	}
	if (N&1) == 0 && hasOddFrequency {
		return true
	}
	return false
}

func solveTestCase(input *TestCaseInputData) string {
	if isClearlyInvalid(input.N, input.A, input.B) {
		return fmt.Sprint(-1)
	}
	concatenatedArrays := make([]int, input.N*4)
	for i := 0; i < input.N; i++ {
		concatenatedArrays[i] = input.A[i]
	}
	for i := 0; i < input.N; i++ {
		concatenatedArrays[input.N+i] = input.B[i]
	}
	for i := 0; i < input.N; i++ {
		concatenatedArrays[2*input.N+i] = input.A[i]
	}
	for i := 0; i < input.N; i++ {
		concatenatedArrays[3*input.N+i] = input.B[i]
	}
	for i := 0; true; i++ {
		L := i
		R := L + input.N + input.N - 1
		if R >= len(concatenatedArrays) {
			break
		}
		if !isPalindrome(i, i+input.N+input.N-1, concatenatedArrays) {
			continue
		}
		if !isValid(i, i+input.N, input.N, concatenatedArrays) {
			continue
		}
		return fmt.Sprint(i)
	}
	return fmt.Sprint(-1)
}
