package main

import "fmt"

func solve(S int, D int, K int) bool {
	bunAmount := (S + D) << 1
	pattyAmount := S + (D << 1)
	cheeseAmount := S + (D << 1)
	return isCheeseBurgerPossibleToBuild(K, bunAmount, pattyAmount, cheeseAmount)
}

func isCheeseBurgerPossibleToBuild(K int, bun int, patty int, cheese int) bool {
	if K+1 > bun {
		return false
	}
	if K > patty {
		return false
	}
	if K > cheese {
		return false
	}
	return true
}

func getResultString(isPossible bool) string {
	if isPossible {
		return "YES"
	}
	return "NO"
}

func solveTestCase(testCase int) {
	var S, D, K int
	_, err := fmt.Scan(&S, &D, &K)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Case #%d: %s\n", testCase, getResultString(solve(S, D, K)))
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
