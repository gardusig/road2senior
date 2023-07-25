# Problem Statement

Given a list of word suggestions and a prefix, create a function that return all suggestions that matches with given prefix.

## Example

Word Suggestions:

* "a"
* "ab"
* "ba"
* "c"
* "e"

Prefix queries:
* "a"
  * ["a", "ab"]
* "b"
  * ["ba"]
* "c"
  * ["c"]
* "e"
  * ["e"]
* ""
  * ["a", "ab", "ba", "c", "e"]
* "z"
  * []

## Solution

One possible solution, with a reasonable time complexity, consists about constructing a [Trie](https://en.wikipedia.org/wiki/Trie) from given word suggestions.

### Time complexity

It takes `O(sum of word lengths)` to construct a Trie.

Each query might take `O(prefix length)` to run. The rest depends on how the output should be structured.

If you want all words explicitly, then it will cost `O(sum of word lengths in the answer)`.

If you wanted only the amount of words, it would cost only `O(1)`. Maybe with some tricks (considering sorted input) you could keep this complexity while returning the index range of words suggestions, like: [2, 3] (indicating that words from index 2 to index 3 matches the prefix).

### Memory

The cost is about the size of the input: `O(word suggestions lengths + prefix length)`
