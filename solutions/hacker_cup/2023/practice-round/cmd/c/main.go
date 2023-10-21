package main

import (
	"fmt"
	"math"
	"sort"
)

var ans int

func isPossible(L int, R int, hasJumped bool, goal int, v []int) bool {
	if L > R {
		return hasJumped
	}
	if L == R {
		if !hasJumped {
			ans = min(ans, goal-v[L])
			return true
		}
		return false
	}
	current := v[L] + v[R]
	if current != goal && hasJumped {
		return false
	}
	ret := false
	if current == goal && isPossible(L+1, R-1, hasJumped, goal, v) {
		ret = true
	}
	if !hasJumped && goal-v[R] > 0 && isPossible(L, R-1, true, goal, v) {
		ans = min(ans, goal-v[R])
		ret = true
	}
	if !hasJumped && goal-v[L] > 0 && isPossible(L+1, R, true, goal, v) {
		ans = min(ans, goal-v[L])
		ret = true
	}
	return ret
}

func solve(v []int, N int) int {
	if N == 1 {
		return 1
	}
	sort.Slice(
		v,
		func(i int, j int) bool {
			return v[i] < v[j]
		},
	)
	if v[0] == v[N-1] {
		return v[0]
	}
	ans = math.MaxInt
	isPossible(0, N-1, false, v[0]+v[N-1], v)
	isPossible(0, N-1, false, v[1]+v[N-1], v)
	isPossible(0, N-1, false, v[0]+v[N-2], v)
	if ans == math.MaxInt {
		ans = -1
	}
	return ans
}

func solveTestCase(testCase int) {
	var N int
	_, err := fmt.Scan(&N)
	if err != nil {
		panic(err)
	}
	N = N + N - 1
	v := make([]int, N)
	for i := 0; i < N; i += 1 {
		_, err := fmt.Scan(&v[i])
		if err != nil {
			panic(err)
		}
	}
	answer := solve(v, N)
	fmt.Printf("Case #%d: %d\n", testCase, answer)
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
