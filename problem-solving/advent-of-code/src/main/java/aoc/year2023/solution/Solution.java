package aoc.year2023.solution;

import aoc.year2023.util.InputReader;
import java.io.IOException;
import java.util.List;

public abstract class Solution<InputDataType, OutputDataType> {
    public abstract OutputDataType solve(InputDataType inputData);

    public abstract InputDataType getInputData();

    protected abstract String getInputUrl();

    protected List<String> getInputLines() {
        try {
            return InputReader.readInputFromUrl(getInputUrl());
        } catch (IOException e) {
            System.err.println("Failed to get inputLines, reason: " + e.getMessage());
            return null;
        }
    }
}
