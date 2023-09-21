package test

import (
	"fmt"
	"testing"

	"github.com/gardusig/road2senior/solutions/countstocks/internal"
)

var smallInputData = [][]int32{
	{},
	{1, 1, 1},
	{1, 1, 2},
	{1, 1},
	{1},
	{2, 1, 1, 2},
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
		fmt.Println("brute: ", answerBrute)
	}
}

func TestSolutionNlogN(t *testing.T) {
	for _, smallInput := range smallInputData {
		answerNlogN := internal.CountStockIntervals(smallInput)
		fmt.Println("answerNlogN: ", answerNlogN)
	}
}
