package aoc.year2023.main;

import aoc.year2023.day1.Day1;
import aoc.year2023.solution.SolutionFactory;

public class Main {
    public static void main(final String[] args) {
        SolutionFactory solutionFactory = new SolutionFactory();
        solutionFactory.registerSolution(1, Day1.class);
        if (args.length != 1) {
            System.err.println("Usage: java <day_number>");
            return;
        }
        try {
            var solution = solutionFactory.createSolution(1);
            if (solution == null) {
                System.err.println("Invalid day number");
                return;
            }
            var inputData = solution.getInputData();
            var outputData = solution.solve(inputData);
            System.out.println("Result: " + outputData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
