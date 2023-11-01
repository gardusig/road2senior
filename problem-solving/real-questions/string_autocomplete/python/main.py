import unittest


class Trie:
    def __init__(self):
        self.edges = {}
        self.word_ending_here = None

    def insert_word(self, word):
        self.__insert_word__(word, 0)

    def get_words_with_prefix_match(self, prefix):
        return self.__get_words_with_prefix_match__(prefix, 0)

    def __insert_word__(self, word, word_index):
        if word_index == len(word):
            self.word_ending_here = word
            return
        c = word[word_index]
        if c not in self.edges:
            self.edges[c] = Trie()
        self.edges[c].__insert_word__(word, word_index + 1)

    def __dfs__(self, words):
        if self.word_ending_here != None:
            words.append(self.word_ending_here)
        for edge in self.edges.values():
            edge.__dfs__(words)

    def __get_words_with_prefix_match__(self, prefix, prefix_idx):
        if prefix_idx == len(prefix):
            words = []
            self.__dfs__(words)
            return words
        c = prefix[prefix_idx]
        if c not in self.edges:
            return []
        return self.edges[c].__get_words_with_prefix_match__(prefix, prefix_idx + 1)


class TestTrie(unittest.TestCase):

    def setUp(self):
        self.trie = Trie()
        with open('resources/input.txt') as f:
            for word in f:
                self.trie.insert_word(word.strip())

    def test_with_simple_query(self):
        expected_output = [
            'hire',
            'hireable',
            'hired',
            'hireless',
            'hireling',
            'hirelings',
            'hireman',
            'hiren',
            'hirer',
            'hirers',
            'hires'
        ]
        actual_output = self.trie.get_words_with_prefix_match('hire')
        self.assertEqual(expected_output, actual_output)


if __name__ == '__main__':
    unittest.main()
