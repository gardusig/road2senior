package main

import (
	"fmt"
	"sort"
	"strconv"
	"strings"
)

type TestCaseInputData struct {
	N int
}

type SliceWithSum struct {
	Slice []int
	Sum   int
}

func generateSlices(currentArray []int, slices *[]SliceWithSum, memo map[string]bool) {
	sort.Ints(currentArray)
	key := fmt.Sprintf("%v", currentArray)
	if memo[key] {
		return
	}
	memo[key] = true
	currentSum := 0
	for _, num := range currentArray {
		currentSum += num
	}
	if currentSum > 41 {
		return
	}
	*slices = append(*slices, SliceWithSum{
		Slice: append([]int{}, currentArray...),
		Sum:   currentSum,
	})
	for i := 0; i < len(currentArray); i++ {
		for j := i + 1; j < len(currentArray); j++ {
			mergedValue := currentArray[i] * currentArray[j]
			newSlice := []int{}
			for k := 0; k < len(currentArray); k++ {
				if k != i && k != j {
					newSlice = append(newSlice, currentArray[k])
				}
			}
			newSlice = append(newSlice, mergedValue)
			generateSlices(newSlice, slices, memo)
		}
	}
}

func generateArrays(factors []int) []SliceWithSum {
	result := []SliceWithSum{}
	memo := make(map[string]bool)
	generateSlices(factors, &result, memo)
	return result
}

func mapToArray(factors map[int]int) []int {
	result := []int{}
	for key, value := range factors {
		for i := 0; i < value; i++ {
			result = append(result, key)
		}
	}
	return result
}

func buildAnswer(N int, factors []int) string {
	elements := make([]string, 0)
	for i := 0; i < N; i++ {
		elements = append(elements, "1")
	}
	for _, value := range factors {
		elements = append(elements, strconv.Itoa(value))
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
	arrays := generateArrays(mapToArray(factors))
	if len(arrays) == 0 {
		return "-1"
	}
	best := arrays[0]
	for _, kappa := range arrays {
		if kappa.Sum > best.Sum || (kappa.Sum == best.Sum && len(kappa.Slice) < len(best.Slice)) {
			best = kappa
		}
	}
	return buildAnswer(41-best.Sum, best.Slice)
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
		go solveTestCase(&testCasesInputData[testCase], testCaseOutputList[testCase])
	}
	for testCase := 0; testCase < testCases; testCase++ {
		fmt.Printf("Case #%d: %s\n", testCase+1, <-testCaseOutputList[testCase])
	}
}
