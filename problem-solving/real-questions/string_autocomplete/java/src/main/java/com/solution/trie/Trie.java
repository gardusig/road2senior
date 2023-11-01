package com.solution.trie;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map.Entry;

public class Trie {

    private final LinkedHashMap<Character, Trie> edges;

    private String wordEndingHere;

    public Trie() {
        this.edges = new LinkedHashMap<>();
        wordEndingHere = null;
    }

    public void addWord(final String word) throws Exception {
        if (word == null) {
            throw new Exception("can not add null word");
        }
        this.addWord(word, 0);
    }

    public ArrayList<String> getWordsWithPrefixMatch(final String prefix) throws Exception {
        if (prefix == null) {
            throw new Exception("can not get words with null prefix");
        }
        return this.getWordsWithPrefixMatch(prefix, 0);
    }

    private void addWord(final String word, final int wordIndex) {
        if (wordIndex == word.length()) {
            this.wordEndingHere = word;
            return;
        }
        final char c = word.charAt(wordIndex);
        if (!this.edges.containsKey(c)) {
            this.edges.put(c, new Trie());
        }
        this.edges.get(c).addWord(word, wordIndex + 1);
    }

    private ArrayList<String> getWordsWithPrefixMatch(final String prefix, final int wordIndex) {
        if (wordIndex == prefix.length()) {
            ArrayList<String> words = new ArrayList<>();
            this.appendAllWordsWithPrefix(words);
            return words;
        }
        final char c = prefix.charAt(wordIndex);
        if (!this.edges.containsKey(c)) {
            return new ArrayList<>();
        }
        return this.edges.get(c).getWordsWithPrefixMatch(prefix, wordIndex + 1);
    }

    private void appendAllWordsWithPrefix(final ArrayList<String> words) {
        if (this.wordEndingHere != null) {
            words.add(this.wordEndingHere);
        }
        for (final Entry<Character, Trie> edge : edges.entrySet()) {
            edge.getValue().appendAllWordsWithPrefix(words);
        }
    }
}
