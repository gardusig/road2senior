package aoc.solution;

import java.util.Map;
import java.util.HashMap;
import java.lang.reflect.InvocationTargetException;

public class SolutionFactory {
    private Map<Integer, Class<?>> dayClasses = new HashMap<>();

    public <InputDataType, OutputDataType> void registerSolution(
            int dayNumber,
            Class<? extends Solution<InputDataType, OutputDataType>> dayClass) {
        dayClasses.put(dayNumber, dayClass);
    }

    @SuppressWarnings("unchecked")
    public <InputDataType, OutputDataType> Solution<InputDataType, OutputDataType> createSolution(int dayNumber)
            throws IllegalAccessException, InstantiationException, NoSuchMethodException, InvocationTargetException {
        var solutionClass = (Class<? extends Solution<InputDataType, OutputDataType>>) dayClasses.get(dayNumber);
        if (solutionClass == null) {
            return null;
        }
        try {
            var constructor = solutionClass.getDeclaredConstructor();
            return constructor.newInstance();
        } catch (InstantiationException | IllegalAccessException | NoSuchMethodException
                | InvocationTargetException e) {
            e.printStackTrace();
            return null;
        }
    }
}
