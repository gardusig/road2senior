package main

import "fmt"

func rawSolve(A int, B int, C int) int {
	best := 0
	maxSingleAmount := C / A
	maxDoubleAmount := C / B
	for qtySingle := max(0, maxSingleAmount-1); qtySingle <= maxSingleAmount; qtySingle += 1 {
		qtyDouble := (C - (qtySingle * A)) / B
		best = max(best, solve(qtySingle, qtyDouble))
	}
	for qtyDouble := max(0, maxDoubleAmount-1); qtyDouble <= maxDoubleAmount; qtyDouble += 1 {
		qtySingle := (C - (qtyDouble * B)) / A
		best = max(best, solve(qtySingle, qtyDouble))
	}
	return best
}

func solve(S int, D int) int {
	bunAmount := (S + D) << 1
	pattyAmount := S + (D << 1)
	cheeseAmount := S + (D << 1)
	return guessMaxCheeseBurgerDeckerSize(bunAmount, pattyAmount, cheeseAmount)
}

func guessMaxCheeseBurgerDeckerSize(bun int, patty int, cheese int) int {
	lo := 1
	hi := 20123456789012345
	for lo <= hi {
		mid := lo + ((hi - lo) >> 1)
		if isCheeseBurgerPossibleToBuild(mid, bun, patty, cheese) {
			lo = mid + 1
		} else {
			hi = mid - 1
		}
	}
	return lo - 1
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

func solveTestCase(testCase int) {
	var A, B, C int
	_, err := fmt.Scan(&A, &B, &C)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Case #%d: %d\n", testCase, rawSolve(A, B, C))
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
