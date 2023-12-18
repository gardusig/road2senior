package aoc.year2023.day1;

import java.util.List;
import org.junit.jupiter.api.Test;

import aoc.util.InputOutputPair;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class Day1Test {
        private Day1 solution;

        public Day1Test() {
                solution = new Day1();
        }

        @Test
        public void testExampleInput() {
                final var exampleInput = List.of(
                                "1abc2",
                                "pqr3stu8vwx",
                                "a1b2c3d4e5f",
                                "treb7uchet");
                final Long expectedOutput = 142L;
                assertEquals(
                                expectedOutput,
                                solution.solve(exampleInput));
        }

        @Test
        public void testCustomInput() {
                final var customTestData = generateCustomTestData();
                for (final var test : customTestData) {
                        assertEquals(
                                        test.getExpectedOutput(),
                                        solution.solve(test.getInput()));
                }
        }

        private List<InputOutputPair<List<String>, Long>> generateCustomTestData() {
                return List.of(
                                new InputOutputPair<>(
                                                List.of(
                                                                "0",
                                                                "pqr1s2tu8vwx"),
                                                18L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "10",
                                                                "pqr1s2tu8vwx"),
                                                28L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "100",
                                                                "pqr1s2tu8vwx"),
                                                28L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "010",
                                                                "pqr1s2tu8vwx"),
                                                18L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "pqr1s2tu8vwx",
                                                                "010"),
                                                18L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "pqr1s2tu8vwx",
                                                                "1010"),
                                                28L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "0"),
                                                0L),
                                new InputOutputPair<>(
                                                List.of(
                                                                ""),
                                                0L),
                                new InputOutputPair<>(
                                                List.of(
                                                                "1"),
                                                11L));
        }
}
