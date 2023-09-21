package internal

import (
	"fmt"
	"math"
	"sort"
)

func CountStockIntervals(stocks []int32) int64 {
	ans := int64(0)
	ans += countIntervalsWithOneStrictlyGreaterBorder(stocks)
	return ans
}

func countIntervalsWithOneStrictlyGreaterBorder(array []int32) int64 {
	compressedArray := getCompressedArray(array)
	fmt.Println("array: ", array)
	fmt.Println("compressed: ", compressedArray)
	total := int64(0)
	total += countIntervalsWithStrictlyGreaterLeftBorder(compressedArray)
	total += countIntervalsWithStrictlyGreaterRightBorder(compressedArray)
	return total
}

// gets min R for each index, where v[R] >= v[L] and R > L
// so v[L] is strictly greater than all values at indexes from L + 1 to R - 1
func countIntervalsWithStrictlyGreaterLeftBorder(compressedArray []int) int64 {
	length := len(compressedArray)
	intervals := 0
	bit := NewMinRangeFenwickTree(length + 5)
	bit.UpdateMin(length, length)
	for i := length - 1; i >= 0; i -= 1 {
		L := i
		R := min(length, bit.QueryMin(length-compressedArray[i]))
		bit.UpdateMin(length-compressedArray[i], i)
		fmt.Println("L: ", L, ", R: ", R)
		intervals += max(0, R-L-1)
	}
	fmt.Println("total intervals with fixed L: ", intervals)
	return int64(intervals)
}

// gets max L for each index, where v[L] >= v[R] and L < R
// so v[R] is strictly greater than all values at indexes from L + 1 to R - 1
func countIntervalsWithStrictlyGreaterRightBorder(compressedArray []int) int64 {
	length := len(compressedArray)
	intervals := 0
	bit := NewMaxRangeFenwickTree(length + 5)
	for i := 0; i < length; i += 1 {
		R := i
		L := max(0, bit.QueryMax(length-compressedArray[i]))
		bit.UpdateMax(length-compressedArray[i], i)
		fmt.Println("L: ", L, ", R: ", R)
		intervals += max(0, R-L-1)
	}
	fmt.Println("total intervals with fixed R: ", intervals)
	return int64(intervals)
}

type FenwickTree struct {
	accum []int
}

func NewMinRangeFenwickTree(size int) *FenwickTree {
	return &FenwickTree{
		accum: getArrayForMinimumRangeFenwickTree(size),
	}
}

func NewMaxRangeFenwickTree(size int) *FenwickTree {
	return &FenwickTree{
		accum: getArrayForMaxRangeFenwickTree(size),
	}
}

func (t *FenwickTree) UpdateMin(index int, value int) {
	for i := index; i < len(t.accum); i += (i & -i) {
		t.accum[i] = min(t.accum[i], value)
	}
}

func (t *FenwickTree) QueryMin(index int) int {
	mn := math.MaxInt
	for i := index; i > 0; i -= (i & -i) {
		mn = min(mn, t.accum[i])
	}
	return mn
}

func (t *FenwickTree) UpdateMax(index int, value int) {
	for i := index; i < len(t.accum); i += (i & -i) {
		t.accum[i] = max(t.accum[i], value)
	}
}

func (t *FenwickTree) QueryMax(index int) int {
	mx := math.MinInt
	for i := index; i > 0; i -= (i & -i) {
		mx = max(mx, t.accum[i])
	}
	return mx
}

func getArrayForMinimumRangeFenwickTree(size int) []int {
	arr := make([]int, size)
	for i := range arr {
		arr[i] = math.MaxInt
	}
	return arr
}

func getArrayForMaxRangeFenwickTree(size int) []int {
	arr := make([]int, size)
	for i := range arr {
		arr[i] = math.MinInt
	}
	return arr
}

func getCompressedArray(arr []int32) []int {
	valueToFrequencyMap := make(map[int32]bool)
	for _, stock := range arr {
		valueToFrequencyMap[stock] = true
	}
	uniqueValueArray := make([]int32, 0, len(arr))
	for key := range valueToFrequencyMap {
		uniqueValueArray = append(uniqueValueArray, key)
	}
	sort.Slice(
		uniqueValueArray,
		func(i int, j int) bool {
			return uniqueValueArray[i] < uniqueValueArray[j]
		},
	)
	valueToOrderedIndexMap := make(map[int32]int)
	for idx := range uniqueValueArray {
		valueToOrderedIndexMap[uniqueValueArray[idx]] = idx
	}
	compressedArray := make([]int, 0, len(arr))
	for idx := range arr {
		newValue := valueToOrderedIndexMap[arr[idx]]
		compressedArray = append(compressedArray, newValue)
	}
	return compressedArray
}
