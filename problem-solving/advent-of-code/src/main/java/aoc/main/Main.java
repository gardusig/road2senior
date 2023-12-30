package aoc.main;

import aoc.solution.SolutionFactory;
import aoc.year2023.day1.Day1;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Main {
    private static final Logger logger = LoggerFactory.getLogger(Main.class);

    private static SolutionFactory solutionFactory;

    static {
        initializeSolutionFactory();
    }

    public static void main(final String[] commandLineArguments) throws Exception {
        try {
            var solutionDayNumber = getSolutionDayNumber(commandLineArguments);
            executeSolution(solutionDayNumber);
        } catch (NumberFormatException e) {
            logger.error("Invalid day number. Please provide a valid integer.");
        } catch (Exception e) {
            logger.error("An error occurred while executing the solution.", e);
        }
    }

    private static void initializeSolutionFactory() {
        solutionFactory = new SolutionFactory();
        // TODO automate registration discovery
        solutionFactory.registerSolution(1, Day1.class);
    }

    private static int getSolutionDayNumber(final String[] commandLineArguments) {
        if (commandLineArguments.length != 1) {
            logger.error("Usage: gradle run --args=\"<day_number>\"");
        }
        return Integer.parseInt(commandLineArguments[0]);
    }

    private static void executeSolution(int solutionDayNumber) throws Exception {
        var solution = solutionFactory.createSolution(solutionDayNumber);
        if (solution == null) {
            logger.error("Invalid day number");
            return;
        }
        var inputData = solution.getInputData();
        var outputData = solution.solve(inputData);
        logger.info("Result: {}", outputData);
    }
}
