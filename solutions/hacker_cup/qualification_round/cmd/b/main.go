package main

import "fmt"

func getResultString(R int, C int) string {
	if R > C {
		return "YES"
	}
	return "NO"
}

func solveTestCase(testCase int) {
	var R, C, A, B int
	_, err := fmt.Scan(&R, &C, &A, &B)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Case #%d: %s\n", testCase, getResultString(R, C))
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
