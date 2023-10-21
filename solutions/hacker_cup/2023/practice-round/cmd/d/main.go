package main

import (
	"fmt"
	"math"
)

const maxJumpSize = 20

type Pair struct {
	First  int
	Second int
}

func NewPair(first int, second int) Pair {
	return Pair{
		First:  first,
		Second: second,
	}
}

func markGraphBridges(N int, graph []map[int]bool) {
	visited := make([]bool, N)
	parent := make([]int, N)
	disc := make([]int, N)
	low := make([]int, N)
	time := 0
	var dfsBridge func(node int)
	dfsBridge = func(node int) {
		visited[node] = true
		disc[node] = time
		low[node] = time
		time++
		for neighbor := range graph[node] {
			if !visited[neighbor] {
				parent[neighbor] = node
				dfsBridge(neighbor)
				low[node] = min(low[node], low[neighbor])
				if low[neighbor] > disc[node] {
					graph[node][neighbor] = true
					graph[neighbor][node] = true
				}
			} else if neighbor != parent[node] {
				low[node] = min(low[node], disc[neighbor])
			}
		}
	}
	for i := 0; i < N; i++ {
		if !visited[i] {
			dfsBridge(i)
		}
	}
}

func getGraphComponents(N int, inputGraph []map[int]bool) (int, []int) {
	componentIndex := 0
	componentByNode := make([]int, N)
	visited := make([]bool, N)
	var dfsComponent func(node int)
	dfsComponent = func(node int) {
		visited[node] = true
		componentByNode[node] = componentIndex
		for neighbor, isBridge := range inputGraph[node] {
			if visited[neighbor] || isBridge {
				continue
			}
			dfsComponent(neighbor)
		}
	}
	for i := 0; i < N; i += 1 {
		if !visited[i] {
			dfsComponent(i)
			componentIndex += 1
		}
	}
	return componentIndex, componentByNode
}

func getComponentsWithOddCycle(N int, inputGraph []map[int]bool, componentQuantity int, componentByNode []int) []bool {
	componentContainsOddCycle := make([]bool, componentQuantity)
	nodeColor := make([]int, N)
	for i := 0; i < N; i += 1 {
		nodeColor[i] = -1
	}
	var dfsIsTwoColorable func(node int, color int) bool
	dfsIsTwoColorable = func(node int, color int) bool {
		nodeColor[node] = color
		ans := true
		for neighbor, isBridge := range inputGraph[node] {
			if isBridge {
				continue
			}
			if nodeColor[neighbor] == -1 && !dfsIsTwoColorable(neighbor, color^1) {
				ans = false
			}
			ans = ans && (nodeColor[neighbor] != color)
		}
		return ans
	}
	for i := 0; i < N; i += 1 {
		if nodeColor[i] == -1 {
			componentContainsOddCycle[componentByNode[i]] = !dfsIsTwoColorable(i, 0)
		}
	}
	return componentContainsOddCycle
}

func buildGraphTreeFromComponents(componentQuantity int, componentByNode []int, inputEdges []Pair) [][]int {
	tree := make([][]int, componentQuantity)
	for i := 0; i < componentQuantity; i += 1 {
		tree[i] = make([]int, 0)
	}
	for _, edge := range inputEdges {
		x := componentByNode[edge.First]
		y := componentByNode[edge.Second]
		if x == y {
			continue
		}
		tree[x] = append(tree[x], y)
		tree[y] = append(tree[y], x)
	}
	return tree
}

func getDistanceOfClosestComponentWithOddCycle(N int, tree [][]int, componentsWithOddCycle []bool) []int {
	distance := make([]int, N)
	queue := make([]int, 0)
	for i := 0; i < N; i += 1 {
		if !componentsWithOddCycle[i] {
			distance[i] = math.MaxInt
			continue
		}
		distance[i] = 0
		queue = append(queue, i)
	}
	queue_index := 0
	for {
		if queue_index >= len(queue) {
			break
		}
		node := queue[queue_index]
		queue_index += 1
		for _, nxt := range tree[node] {
			if distance[nxt] <= distance[node]+1 {
				continue
			}
			distance[nxt] = distance[node] + 1
			queue = append(queue, nxt)
		}
	}
	return distance
}

func buildLcaTree(N int, nodeValue []int, tree [][]int) ([]int, [][]int, [][]int) {
	depth := make([]int, N)
	lca := make([][]int, N)
	minDistance := make([][]int, N)
	for i := 0; i < N; i += 1 {
		lca[i] = make([]int, maxJumpSize)
		minDistance[i] = make([]int, maxJumpSize)
	}
	var dfs func(node int, parent int)
	dfs = func(node int, parent int) {
		depth[node] = depth[parent] + 1
		lca[node][0] = parent
		minDistance[node][0] = min(nodeValue[node], nodeValue[parent])
		for jumpSize := 1; jumpSize < maxJumpSize; jumpSize += 1 {
			lca[node][jumpSize] = lca[lca[node][jumpSize-1]][jumpSize-1]
			minDistance[node][jumpSize] = min(
				minDistance[node][jumpSize-1],
				minDistance[lca[node][jumpSize-1]][jumpSize-1],
			)
		}
		for _, nxt := range tree[node] {
			if nxt == parent {
				continue
			}
			dfs(nxt, node)
		}
	}
	depth[0] = -1
	dfs(0, 0)
	return depth, lca, minDistance
}

func getQueryResult(x int, y int, depth []int, lca [][]int, minDistance [][]int, nodeValue []int, queries []Pair) int {
	if depth[x] < depth[y] {
		x, y = y, x
	}
	answer := nodeValue[x]
	depthDifference := depth[x] - depth[y]
	for jumpSize := maxJumpSize - 1; jumpSize >= 0; jumpSize -= 1 {
		if (depthDifference & (1 << jumpSize)) > 0 {
			answer = min(answer, minDistance[x][jumpSize])
			x = lca[x][jumpSize]
		}
	}
	if x == y {
		return answer
	}
	for jumpSize := maxJumpSize - 1; jumpSize >= 0; jumpSize-- {
		if lca[x][jumpSize] != lca[y][jumpSize] {
			answer = min(answer, min(minDistance[x][jumpSize], minDistance[y][jumpSize]))
			x = lca[x][jumpSize]
			y = lca[y][jumpSize]
		}
	}
	answer = min(answer, minDistance[x][0])
	answer = min(answer, minDistance[y][0])
	return answer
}

func getQueryResultSum(depth []int, lca [][]int, minDistance [][]int, queries []Pair, nodeValue []int, componentByNode []int) int {
	answer := 0
	for _, query := range queries {
		x := componentByNode[query.First]
		y := componentByNode[query.Second]
		result := getQueryResult(x, y, depth, lca, minDistance, nodeValue, queries)
		if result == math.MaxInt {
			result = -1
		}
		answer += result
	}
	return answer
}

func solve(N int, M int, inputEdges []Pair, inputGraph []map[int]bool, queries []Pair) int {
	markGraphBridges(N, inputGraph)
	componentQuantity, componentByNode := getGraphComponents(N, inputGraph)
	tree := buildGraphTreeFromComponents(componentQuantity, componentByNode, inputEdges)
	componentsWithOddCycle := getComponentsWithOddCycle(N, inputGraph, componentQuantity, componentByNode)
	distanceToClosestComponentWithOddCycle := getDistanceOfClosestComponentWithOddCycle(componentQuantity, tree, componentsWithOddCycle)
	depth, lca, minDistance := buildLcaTree(componentQuantity, distanceToClosestComponentWithOddCycle, tree)
	return getQueryResultSum(depth, lca, minDistance, queries, distanceToClosestComponentWithOddCycle, componentByNode)
}

func solveTestCase(testCase int) {
	var N, M int
	_, err := fmt.Scan(&N, &M)
	if err != nil {
		panic(err)
	}
	inputEdges := make([]Pair, M)
	inputGraph := make([]map[int]bool, N)
	for i := 0; i < N; i += 1 {
		inputGraph[i] = make(map[int]bool)
	}
	for edgeIndex := 0; edgeIndex < M; edgeIndex += 1 {
		var x, y int
		_, err := fmt.Scan(&x, &y)
		if err != nil {
			panic(err)
		}
		x -= 1
		y -= 1
		inputGraph[x][y] = false
		inputGraph[y][x] = false
		inputEdges[edgeIndex] = NewPair(x, y)
	}
	var Q int
	_, err = fmt.Scan(&Q)
	if err != nil {
		panic(err)
	}
	queries := make([]Pair, Q)
	for queryIndex := 0; queryIndex < Q; queryIndex += 1 {
		var x, y int
		_, err := fmt.Scan(&x, &y)
		if err != nil {
			panic(err)
		}
		x -= 1
		y -= 1
		queries[queryIndex] = NewPair(x, y)
	}
	answer := solve(N, M, inputEdges, inputGraph, queries)
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
