package aoc.util;

public class InputOutputPair<A, B> {
    private A input;
    private B expectedOutput;

    public InputOutputPair(A input, B output) {
        this.input = input;
        this.expectedOutput = output;
    }

    public A getInput() {
        return input;
    }

    public B getExpectedOutput() {
        return expectedOutput;
    }
}
