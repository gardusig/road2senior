package com.solution.trie;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class TrieTests {

    private static final String RANDOM_STRING = "a0123AASDBNQKWEJB12BKJABWDKJQH";
    private static final String INPUT_FILEPATH = "src/test/resources/input.txt";

    @Test
    void whenEmptyTrie() throws Exception {
        final Trie trie = new Trie();
        assertEquals(trie.getWordsWithPrefixMatch(""), new ArrayList<>());
        assertEquals(trie.getWordsWithPrefixMatch("a"), new ArrayList<>());
        assertEquals(trie.getWordsWithPrefixMatch("abc"), new ArrayList<>());
        assertEquals(trie.getWordsWithPrefixMatch(RANDOM_STRING), new ArrayList<>());
    }

    @Test
    void whenInsertedNullWord() {
        final Trie trie = new Trie();
        final Exception exception = assertThrows(Exception.class, () -> trie.addWord(null));
        assertEquals("can not add null word", exception.getMessage());
    }

    @Test
    void whenNullQuery() {
        final Trie trie = new Trie();
        final Exception exception = assertThrows(Exception.class, () -> trie.getWordsWithPrefixMatch(null));
        assertEquals("can not get words with null prefix", exception.getMessage());
    }

    @Test
    void whenSimpleInsertionsAndQueries() throws Exception {
        final Trie trie = new Trie();
        final List<String> words = Arrays.asList("a", "ab", "ba", "cd", "e");
        for (final String word : words) {
            trie.addWord(word);
        }
        assertEquals(trie.getWordsWithPrefixMatch("a"), Arrays.asList("a", "ab"));
        assertEquals(trie.getWordsWithPrefixMatch("b"), Collections.singletonList("ba"));
        assertEquals(trie.getWordsWithPrefixMatch("c"), Collections.singletonList("cd"));
        assertEquals(trie.getWordsWithPrefixMatch("e"), Collections.singletonList("e"));
        assertEquals(trie.getWordsWithPrefixMatch(RANDOM_STRING), new ArrayList<>());
        assertEquals(trie.getWordsWithPrefixMatch(""), Arrays.asList("a", "ab", "ba", "cd", "e"));
        trie.addWord(RANDOM_STRING);
        assertEquals(trie.getWordsWithPrefixMatch(RANDOM_STRING), Collections.singletonList(RANDOM_STRING));
        assertEquals(trie.getWordsWithPrefixMatch(""), Arrays.asList("a", "ab", RANDOM_STRING, "ba", "cd", "e"));
    }

    @Test
    void whenInsertionOrderMatter() throws Exception {
        final Trie trie = new Trie();
        final List<String> words = Arrays.asList("a", "ab");
        for (final String word : words) {
            trie.addWord(word);
        }
        assertNotEquals(trie.getWordsWithPrefixMatch("a"), Arrays.asList("ab", "a"));
        assertEquals(trie.getWordsWithPrefixMatch("a"), Arrays.asList("a", "ab"));
    }

    @Test
    void whenStressTest() throws Exception {
        final Trie trie = new Trie();
        final BufferedReader br = new BufferedReader(new FileReader(INPUT_FILEPATH));
        String line;
        while (true) {
            line = br.readLine();
            if (line == null) {
                break;
            }
            trie.addWord(line);
        }
        final List<String> HIRE_ME = Arrays.asList(
                "hire",
                "hireable",
                "hired",
                "hireless",
                "hireling",
                "hirelings",
                "hireman",
                "hiren",
                "hirer",
                "hirers",
                "hires");
        assertEquals(trie.getWordsWithPrefixMatch("hire"), HIRE_ME);
        br.close();
    }
}
