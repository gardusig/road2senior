#include <bits/stdc++.h>

void solve_test_case(const int test) {
  int N;
  std::string s;
  std::cin >> N >> s;
  char last = '$';
  int ans = 0;
  for (const char c : s) {
    if ((c == 'X' and last == 'O') or (c == 'O' and last == 'X')) {
      ans += 1;
    }
    if (c != 'F') {
      last = c;
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