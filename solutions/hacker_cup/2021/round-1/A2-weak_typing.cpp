#include <bits/stdc++.h>

const int MOD = 1'000'000'000 + 7;

void solve_test_case(const int test) {
  int N;
  std::string s;
  std::cin >> N >> s;

  int sum = 0;
  char last = '$';
  int last_pos = -1;
  int current = 0;
  int qty_total = 0;
  std::map<int, int> qty_frequency;
  std::vector<bool> is_marked(N + 5, false);

  for (int i = 0; i < N; i += 1) {
    const char c = s[i];
    if ((c == 'X' and last == 'O') or (c == 'O' and last == 'X')) {
      current += 1;
      is_marked[last_pos] = true;
    }
    if (c != 'F') {
      last = c;
      last_pos = i;
    }
    sum = (sum + current) % MOD;
    qty_total += 1;
    qty_frequency[current] += 1;
  }

  int ans = 0;
  int current_frequency = 0;
  for (int i = 0; i < N; i += 1) {
    ans = (ans + sum) % MOD;
    if (is_marked[i]) {
      qty_total -= qty_frequency[current_frequency];
      current_frequency += 1;
      sum = (0LL + sum - qty_total + MOD) % MOD;
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