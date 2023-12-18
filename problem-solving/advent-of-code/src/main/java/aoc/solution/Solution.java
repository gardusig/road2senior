package aoc.solution;

import aoc.client.Client;
import java.util.stream.Stream;

public abstract class Solution<InputDataType, OutputDataType> {
    protected final Client client;

    public Solution(final int year, final int day) {
        this.client = new Client(year, day);
    }

    public abstract OutputDataType solve(InputDataType inputData);

    protected abstract InputDataType getParsedInputData(Stream<String> rawInputData);

    public InputDataType getInputData() {
        var inputLines = this.client.getInput();
        return getParsedInputData(inputLines);
    }
}
