package test

import (
	"fmt"
	"testing"

	"github.com/gardusig/road2senior/solutions/countstocks/internal"
)

var smallInputs = [][]int32{
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

func TestServerSetup(t *testing.T) {
	for _, smallInput := range smallInputs {
		answerBrute := internal.CountStockIntervalsBrute(smallInput)
		fmt.Println("brute: ", answerBrute)
	}
}
