package aoc.year2023.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class InputReader {
    public static List<String> readInputFromUrl(String urlString) throws IOException {
        List<String> inputLines = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new URL(urlString).openStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                inputLines.add(line);
            }
        }
        return inputLines;
    }
}
