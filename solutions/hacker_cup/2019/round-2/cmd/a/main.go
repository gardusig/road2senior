package main

import "fmt"

func getCellColor(R int, C int) bool {
	if (R & 1) == 1 {
		return (C & 1) > 0
	}
	return !((C & 1) > 0)
}

func isForcedToSurrender(A int, B int, K int, R []int, C []int) bool {
	if K < 2 {
		return false
	}
	for i := 0; i < K; i += 1 {
		if getCellColor(A, B) != getCellColor(R[i], C[i]) {
			return false
		}
	}
	return true
}

func getResultString(yes bool) string {
	if yes {
		return "Y"
	}
	return "N"
}

func solveTestCase(testCase int) {
	var N, M, K int
	_, err := fmt.Scan(&N, &M, &K)
	if err != nil {
		panic(err)
	}
	var A, B int
	_, err = fmt.Scan(&A, &B)
	if err != nil {
		panic(err)
	}
	R := make([]int, K)
	C := make([]int, K)
	for i := 0; i < K; i += 1 {
		_, err = fmt.Scan(&R[i], &C[i])
		if err != nil {
			panic(err)
		}
	}
	answer := getResultString(isForcedToSurrender(A, B, K, R, C))
	fmt.Printf("Case #%d: %s\n", testCase, answer)
}

func main() {
	var testCases int
	_, err := fmt.Scan(&testCases)
	if err != nil {
		panic(err)
	}
	for testCase := 1; testCase <= testCases; testCase += 1 {
		solveTestCase(testCase)
	}
}
