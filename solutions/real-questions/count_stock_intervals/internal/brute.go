package internal

import (
	"github.com/sirupsen/logrus"
)

func CountStockIntervalsBrute(stocks []int32) int64 {
	intervals := make(map[int32]map[int32]bool)
	for _, mustReverse := range []bool{false, true} {
		countStockIntervalsBruteHelper(stocks, intervals, mustReverse)
	}
	ans := int64(0)
	for L, mp := range intervals {
		ans += int64(len(mp))
		for R := range mp {
			logrus.Debug("L: ", L, ", R: ", R)
		}
	}
	return ans
}

func addIntervalToMap(intervalMap map[int32]map[int32]bool, L int32, R int32, N int32, isReversed bool) {
	if isReversed == true {
		L, R = R, L
		L = N - L - 1
		R = N - R - 1
	}
	if _, ok := intervalMap[L]; !ok {
		intervalMap[L] = make(map[int32]bool)
	}
	intervalMap[L][R] = true
}

func countStockIntervalsBruteHelper(stocks []int32, intervals map[int32]map[int32]bool, mustReverse bool) {
	length := int32(len(stocks))
	if mustReverse {
		reverseSlice(stocks)
	}
	for indexL := 0; indexL < int(length); indexL += 1 {
		greatest := stocks[indexL]
		for indexR := indexL; indexR < int(length); indexR += 1 {
			greatest = max(greatest, stocks[indexR])
			if !isIntervalValid(greatest, stocks[indexL], stocks[indexR]) {
				continue
			}
			addIntervalToMap(intervals, int32(indexL), int32(indexR), length, false)
		}
	}
	if mustReverse {
		reverseSlice(stocks)
	}
}

func isIntervalValid(greatest int32, leftmostStock int32, rightmostStock int32) bool {
	return leftmostStock >= greatest || rightmostStock >= greatest
}

func reverseSlice(slice []int32) {
	length := len(slice)
	for i := 0; i < length/2; i++ {
		j := length - i - 1
		slice[i], slice[j] = slice[j], slice[i]
	}
}
