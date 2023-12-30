package aoc.year2023.day1;

import aoc.solution.Solution;
import java.util.List;
import java.util.stream.Stream;

public class Day1 extends Solution<List<String>, Long> {
    public Day1() {
        super(2023, 1);
    }

    @Override
    public List<String> getParsedInputData(Stream<String> rawInputData) {
        return rawInputData.toList();
    }

    @Override
    public Long solve(final List<String> inputData) {
        long sum = 0;
        for (final var calibrationValue : inputData) {
            sum += getTwoDigitNumberFromString(calibrationValue.toString());
        }
        return sum;
    }

    private int getTwoDigitNumberFromString(final String s) {
        final char[] characters = s.toCharArray();
        final int firstDigit = getFirstDigitFromString(characters);
        final int lastDigit = getLastDigitFromString(characters);
        return firstDigit * 10 + lastDigit;
    }

    private int getFirstDigitFromString(final char[] characters) {
        for (final char c : characters) {
            if (Character.isDigit(c)) {
                return charToInt(c);
            }
        }
        return 0;
    }

    private int getLastDigitFromString(final char[] characters) {
        for (int i = characters.length - 1; i >= 0; i -= 1) {
            final char c = characters[i];
            if (Character.isDigit(c)) {
                return charToInt(c);
            }
        }
        return 0;
    }

    private int charToInt(char c) {
        return c - '0';
    }
}
