package main

import (
	"fmt"
	"strconv"
	"strings"
)

type TestCaseInputData struct {
	N int
}

func buildAnswer(N int, factors map[int]int) string {
	elements := make([]string, 0)
	for i := 0; i < N; i++ {
		elements = append(elements, "1")
	}
	for key, value := range factors {
		for i := 0; i < value; i++ {
			elements = append(elements, strconv.Itoa(key))
		}
	}
	result := strings.Join(elements, " ")
	length := len(strings.Fields(result))
	return strconv.Itoa(length) + " " + result
}

func factorize(N int) map[int]int {
	factors := make(map[int]int)
	for i := 2; i*i <= N; i++ {
		for N%i == 0 {
			factors[i]++
			N /= i
		}
	}
	if N > 1 {
		factors[N]++
	}
	return factors
}

func solve(N int) string {
	factors := factorize(N)
	// fmt.Println("N:", N)
	// fmt.Println("factors:", factors)
	sum := 0
	for key, value := range factors {
		sum += key * value
	}
	// fmt.Println("sum:", sum)
	if sum > 41 {
		return "-1"
	}
	return buildAnswer(41-sum, factors)
}

func solveTestCase(input *TestCaseInputData, output chan string) {
	answer := solve(
		input.N,
	)
	output <- answer
}

func readTestCaseInputData(input *TestCaseInputData) error {
	_, err := fmt.Scan(&input.N)
	if err != nil {
		return err
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
