#include <bits/stdc++.h>

std::set<char> vowels{'A', 'E', 'I', 'O', 'U'};

bool is_vowel(const char c) { return vowels.count(c); }

void solve_test_case(const int test) {
  std::string s;
  std::cin >> s;
  int vowel_qty = 0;
  int consonant_qty = 0;
  std::map<char, int> char_frequency;
  for (const char c : s) {
    char_frequency[c] += 1;
    if (is_vowel(c)) {
      vowel_qty += 1;
    } else {
      consonant_qty += 1;
    }
  }
  int ans = INT_MAX;
  for (char goal = 'A'; goal <= 'Z'; goal += 1) {
    const int qty = char_frequency[goal];
    if (is_vowel(goal)) {
      vowel_qty -= qty;
      ans = std::min(ans, consonant_qty + (vowel_qty << 1));
      vowel_qty += qty;
    } else {
      consonant_qty -= qty;
      ans = std::min(ans, vowel_qty + (consonant_qty << 1));
      consonant_qty += qty;
    }
  }
  std::cout << "Case #" << test << ": " << ans << '\n';
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}