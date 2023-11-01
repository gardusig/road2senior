#include <bits/stdc++.h>

std::map<int, int> get_line(const int M) {
  std::map<int, int> f;
  for (int i = 0; i < M; i += 1) {
    int value;
    std::cin >> value;
    f[value] += 1;
  }
  return f;
}

int get_diff(std::map<int, int>& x, std::map<int, int>& y) {
  int diff = 0;
  for (const auto pair : y) {
    const int outfit = pair.first;
    const int qty = pair.second;
    diff += std::max(0, qty - x[outfit]);
  }
  return diff;
}

int64_t solve_test_case(const int test) {
  int N, M;
  std::cin >> N >> M;
  int64_t ans = 0;
  std::map<int, int> current_frequency = get_line(M);
  std::map<int, int> start(current_frequency);
  int keep = M;
  for (int i = 0; i < N; i += 1) {
    auto nxt_frequency = get_line(M);
    ans += get_diff(current_frequency, nxt_frequency);
    for (auto& it : start) {
      const int can_move =
          std::max(0, std::min(it.second, current_frequency[it.first] -
                                              nxt_frequency[it.first]));
      const int qty = std::min(can_move, keep);
      it.second -= qty;
      ans -= qty;
      keep -= qty;
    }
    current_frequency = nxt_frequency;
  }
  return std::max(0LL, ans);
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    std::cout << "Case #" << test << ": " << solve_test_case(test) << std::endl;
  }
  return 0;
}