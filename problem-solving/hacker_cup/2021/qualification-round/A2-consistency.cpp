#include <bits/stdc++.h>

void solve_test_case(const int test) {
  std::string s;
  std::cin >> s;
  int K;
  std::cin >> K;
  int64_t cost_to_convert_char[26][26];
  for (int i = 0; i < 26; i += 1) {
    for (int j = 0; j < 26; j += 1) {
      cost_to_convert_char[i][j] = INT32_MAX;
    }
    cost_to_convert_char[i][i] = 0;
  }
  for (int i = 0; i < K; i += 1) {
    std::string edge;
    std::cin >> edge;
    const int from = edge[0] - 'A';
    const int to = edge[1] - 'A';
    cost_to_convert_char[from][to] = 1;
  }
  for (int k = 0; k < 26; k += 1) {
    for (int i = 0; i < 26; i += 1) {
      for (int j = 0; j < 26; j += 1) {
        cost_to_convert_char[i][j] =
            std::min(cost_to_convert_char[i][j],
                     cost_to_convert_char[i][k] + cost_to_convert_char[k][j]);
      }
    }
  }
  std::map<char, int> char_frequency;
  for (const char c : s) {
    char_frequency[c] += 1;
  }
  int64_t ans = INT64_MAX;
  for (int goal = 0; goal < 26; goal += 1) {
    int64_t current = 0;
    for (const auto it : char_frequency) {
      const char c = it.first - 'A';
      const int qty = it.second;
      if (cost_to_convert_char[c][goal] == INT32_MAX) {
        current = INT64_MAX;
        break;
      }
      current += (1LL * qty * cost_to_convert_char[c][goal]);
    }
    ans = std::min(ans, current);
  }
  if (ans == INT64_MAX) {
    ans = -1;
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