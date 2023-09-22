package internal

import (
	"math"
	"sort"

	"github.com/sirupsen/logrus"
)

func CountStockIntervals(stocks []int32) int64 {
	ans := int64(0)
	ans += countIntervalsWithOneStrictlyGreaterBorder(stocks)
	return ans
}

func countIntervalsWithOneStrictlyGreaterBorder(array []int32) int64 {
	compressedArray := getCompressedArray(array)
	logrus.Debug("array: ", array)
	logrus.Debug("compressed: ", compressedArray)
	total := int64(0)
	total += countIntervalsWithGreaterLeftBorder(compressedArray)
	total += countIntervalsWithGreaterRightBorder(compressedArray)
	total += countIntervalsWithEqualBorder(compressedArray)
	return total
}

// gets min R for each index, where v[R] >= v[L] and R > L
// so v[L] is strictly greater than all values at indexes from L + 1 to R - 1
func countIntervalsWithGreaterLeftBorder(compressedArray []int) int64 {
	intervals := 0
	length := len(compressedArray)
	bit := NewMinRangeFenwickTree(length + 1)
	for L := length - 1; L >= 0; L -= 1 {
		R := min(length, bit.QueryMin(length-compressedArray[L]))
		bit.UpdateMin(length-compressedArray[L], L)
		logrus.Debug("L: ", L, ", R: ", R)
		intervals += max(0, R-L-1)
	}
	logrus.Debug("total intervals with fixed L: ", intervals)
	return int64(intervals)
}

// gets max L for each index, where v[L] >= v[R] and L < R
// so v[R] is strictly greater than all values at indexes from L + 1 to R - 1
func countIntervalsWithGreaterRightBorder(compressedArray []int) int64 {
	intervals := 0
	length := len(compressedArray)
	bit := NewMaxRangeFenwickTree(length + 5)
	for R := 0; R < length; R += 1 {
		L := max(-1, bit.QueryMax(length-compressedArray[R]))
		bit.UpdateMax(length-compressedArray[R], R)
		logrus.Debug("L: ", L, ", R: ", R)
		intervals += max(0, R-L-1)
	}
	logrus.Debug("total intervals with fixed R: ", intervals)
	return int64(intervals)
}

// iterates through from the highest to lowest values at compressedArray
// each iteration checks how many consecutive elements can be grouped,
// which means checking if any greater value has appeared between each i and i+1,
// where i is the index of an appearance of value at compressedArray
// like [2, ..., 2] would check if there is anything greater than 2 between them
func countIntervalsWithEqualBorder(compressedArray []int) int64 {
	intervals := 0
	length := len(compressedArray)
	sort.Slice(
		compressedArray,
		func(i int, j int) bool {
			return compressedArray[i] < compressedArray[j]
		},
	)
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

type SortedSet []int

func (s SortedSet) Len() int           { return len(s) }
func (s SortedSet) Less(i, j int) bool { return s[i] < s[j] }
func (s SortedSet) Swap(i, j int)      { s[i], s[j] = s[j], s[i] }

func (s SortedSet) Contains(key int) bool {
	i := sort.Search(len(s), func(i int) bool { return s[i] >= key })
	return i < len(s) && s[i] == key
}

func (s SortedSet) LowerBound(key int) int {
	i := sort.Search(len(s), func(i int) bool { return s[i] >= key })
	return i
}

func (s SortedSet) UpperBound(key int) int {
	i := sort.Search(len(s), func(i int) bool { return s[i] > key })
	return i
}
