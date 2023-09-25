package test

import (
	"fmt"
	"testing"

	"github.com/gardusig/road2senior/solutions/countstocks/real-questions/count_stock_intervals/internal"
)

var smallInputData = [][]int32{
	{},
	{1, 1, 1},
	{1, 1, 2},
	{1, 1},
	{1, 2, 2, 3, 1, 2, 3, 2, 2},
	{1, 2, 2, 3, 1, 2, 1, 3, 2, 2},
	{1},
	{2, 1, 1, 2, 1, 1, 2},
	{2, 1, 1, 2},
	{2, 2, 1, 1, 2, 1, 1, 2, 2},
	{2, 2, 3, 1, 2, 1, 3, 2, 2},
	{3, 2, 1, 2, 3},
	{3, 2, 1, 4, 2, 4, 3, 1},
	{3, 2, 4, 2, 3},
	{3, 2, 4, 2, 4, 3, 1, 2},
	{3, 2, 4, 2, 4, 3, 1},
	{3, 2, 4, 2, 4, 3},
}

func init() {
	// logrus.SetLevel(logrus.DebugLevel)
}

func TestSmallInputData(t *testing.T) {
	for _, smallInput := range smallInputData {
		answerBrute := internal.CountStockIntervalsBrute(smallInput)
		answerNlogN := internal.CountStockIntervals(smallInput)
		fmt.Println("brute: ", answerBrute)
		fmt.Println("answerNlogN: ", answerNlogN)
	}
}
