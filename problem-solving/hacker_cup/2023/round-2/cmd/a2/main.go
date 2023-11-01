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
	M int
	A []string
}

func readTestCaseInputData(input *TestCaseInputData) {
	if _, err := fmt.Scan(&input.N, &input.M); err != nil {
		panic(err)
	}
	input.A = make([]string, input.N)
	for i := 0; i < input.N; i++ {
		if _, err := fmt.Scan(&input.A[i]); err != nil {
			panic(err)
		}
	}
}

var dx = []int{0, 0, 1, -1}
var dy = []int{1, -1, 0, 0}

func isPositionValid(x int, y int, N int, M int, board []string, used [][]bool) bool {
	if (x < 0) || (x >= N) {
		return false
	}
	if (y < 0) || (y >= M) {
		return false
	}
	if used[x][y] {
		return false
	}
	return board[x][y] != 'B'
}

func countComponentSize(i int, j int, N int, M int, board []string, used [][]bool, availableBordersForComponent map[[2]int]bool) int {
	used[i][j] = true
	componentSize := 1
	for k := 0; k < 4; k++ {
		x := i + dx[k]
		y := j + dy[k]
		if !isPositionValid(x, y, N, M, board, used) {
			continue
		}
		if board[x][y] == 'W' {
			componentSize += countComponentSize(x, y, N, M, board, used, availableBordersForComponent)
		} else if board[x][y] == '.' {
			availableBordersForComponent[[2]int{x, y}] = true
		}
	}
	return componentSize
}

func solveTestCase(input *TestCaseInputData) string {
	used := make([][]bool, input.N)
	acquirableStones := make([][]int, input.N)
	for i := 0; i < input.N; i++ {
		used[i] = make([]bool, input.M)
		acquirableStones[i] = make([]int, input.M)
	}
	for i := 0; i < input.N; i++ {
		for j := 0; j < input.M; j++ {
			if input.A[i][j] != 'W' {
				continue
			}
			if used[i][j] {
				continue
			}
			availableBordersForComponent := make(map[[2]int]bool)
			componentSize := countComponentSize(i, j, input.N, input.M, input.A, used, availableBordersForComponent)
			if len(availableBordersForComponent) > 1 {
				continue
			}
			var pair [2]int
			for key := range availableBordersForComponent {
				pair = key
			}
			acquirableStones[pair[0]][pair[1]] += componentSize
		}
	}
	best := 0
	for i := 0; i < input.N; i++ {
		for j := 0; j < input.M; j++ {
			best = max(best, acquirableStones[i][j])
		}
	}
	return fmt.Sprint(best)
}
