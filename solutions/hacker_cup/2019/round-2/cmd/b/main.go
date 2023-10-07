package main

import (
	"fmt"
)

type TestCaseInputData struct {
	N int
	M int
	X []int
	Y []int
}

func findRootOfDisjointSet(x int, disjointSetIndex []int) int {
	if x != disjointSetIndex[x] {
		disjointSetIndex[x] = findRootOfDisjointSet(disjointSetIndex[x], disjointSetIndex)
	}
	return disjointSetIndex[x]
}

func unionDisjointSets(x int, y int, parentIndices []int, setSize []int) {
	rootX := findRootOfDisjointSet(x, parentIndices)
	rootY := findRootOfDisjointSet(y, parentIndices)
	if rootX == rootY {
		return
	}
	if setSize[rootX] < setSize[rootY] {
		rootX, rootY = rootY, rootX
	}
	parentIndices[rootY] = rootX
	setSize[rootX] += setSize[rootY]
}

func joinPalindromePairs(L int, R int, disjointSetParent []int, disjointSetSize []int) {
	for L < R {
		unionDisjointSets(L, R, disjointSetParent, disjointSetSize)
		L++
		R--
	}
}

func findMinDifference(answerLength int, setSizes map[int]int) ([]int, []int) {
	N := len(setSizes)
	setSizesList := make([]int, 0, N)
	setSizesRootList := make([]int, 0, N)
	for disjointSetRoot, size := range setSizes {
		setSizesList = append(setSizesList, size)
		setSizesRootList = append(setSizesRootList, disjointSetRoot)
	}
	dp := make([][]int, N+1)
	for i := range dp {
		dp[i] = make([]int, answerLength/2+1)
	}
	for i := 1; i <= N; i++ {
		for j := 0; j <= answerLength/2; j++ {
			dp[i][j] = dp[i-1][j]
			if j >= setSizesList[i-1] {
				dp[i][j] = max(
					dp[i][j],
					dp[i-1][j-setSizesList[i-1]]+setSizesList[i-1],
				)
			}
		}
	}
	groupA := make([]int, 0)
	groupB := make([]int, 0)
	j := answerLength / 2
	for i := N; i > 0; i-- {
		if j >= setSizesList[i-1] && dp[i][j] == dp[i-1][j-setSizesList[i-1]]+setSizesList[i-1] {
			groupA = append(groupA, setSizesRootList[i-1])
			j -= setSizesList[i-1]
		} else {
			groupB = append(groupB, setSizesRootList[i-1])
		}
	}
	return groupA, groupB
}

func combineAndAssignGroups(N int, groupA []int, groupB []int, disjointSetParent []int) string {
	groupAMap := make(map[int]bool)
	for _, element := range groupA {
		groupAMap[element] = true
	}
	result := make([]byte, N)
	for i := 0; i < N; i++ {
		root := findRootOfDisjointSet(i, disjointSetParent)
		if groupAMap[root] {
			result[i] = '0'
		} else {
			result[i] = '1'
		}
	}
	return string(result)
}

func generateDisjointSet(N int) ([]int, []int) {
	disjointSetParent := make([]int, N)
	disjointSetSize := make([]int, N)
	for i := 0; i < N; i++ {
		disjointSetParent[i] = i
		disjointSetSize[i] = 1
	}
	return disjointSetParent, disjointSetSize
}

func buildDisjointSetFromPalindromePairs(N int, M int, X []int, Y []int) (map[int]int, []int) {
	disjointSetParent, disjointSetSize := generateDisjointSet(N)
	for i := 0; i < M; i++ {
		joinPalindromePairs(X[i], Y[i], disjointSetParent, disjointSetSize)
	}
	setSizes := make(map[int]int)
	for i := 0; i < N; i++ {
		root := findRootOfDisjointSet(i, disjointSetParent)
		setSizes[root]++
	}
	return setSizes, disjointSetParent
}

func solve(N int, M int, X []int, Y []int) string {
	disjointSets, disjointSetsRoot := buildDisjointSetFromPalindromePairs(N, M, X, Y)
	groupA, groupB := findMinDifference(N, disjointSets)
	return combineAndAssignGroups(N, groupA, groupB, disjointSetsRoot)
}

func solveTestCase(input *TestCaseInputData, output chan string) {
	answer := solve(
		input.N,
		input.M,
		input.X,
		input.Y,
	)
	output <- answer
}

func readTestCaseInputData(input *TestCaseInputData) error {
	_, err := fmt.Scan(&input.N, &input.M)
	if err != nil {
		return err
	}
	input.X = make([]int, input.M)
	input.Y = make([]int, input.M)
	for i := 0; i < input.M; i++ {
		_, err = fmt.Scan(&input.X[i], &input.Y[i])
		if err != nil {
			return err
		}
		input.X[i]--
		input.Y[i]--
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
