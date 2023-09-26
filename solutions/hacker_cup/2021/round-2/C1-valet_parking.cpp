#include <bits/stdc++.h>

int64_t solve(const int N, const int M, const int K,
              std::vector<std::string> v) {
  v.push_back(std::string(M, '.'));
  int64_t best = LLONG_MAX;
  std::vector<int> qty(M, 0);
  for (int i = 0; i < K; i += 1) {
    for (int j = 0; j < M; j += 1) {
      if (v[i][j] == 'X') {
        qty[j] += 1;
      }
    }
  }
  for (int i = K; i < N; i += 1) {
    for (int j = 0; j < M; j += 1) {
      if (v[i][j] == 'X') {
        qty[j] += 1;
      }
    }
    int64_t current = (i - K + 1);
    for (int j = 0; j < M; j += 1) {
      if (qty[j] > K or v[i + 1][j] == 'X') {
        current += 1;
      }
    }
    best = std::min(best, current);
  }
  return best;
}

int64_t solve_test_case(const int test) {
  int N, M, K;
  std::cin >> N >> M >> K;
  std::vector<std::string> v(N);
  for (int i = 0; i < N; i += 1) {
    std::cin >> v[i];
  }

  int64_t ans = 0;
  K -= 1;
  for (int j = 0; j < M; j += 1) {
    ans += (v[K][j] == 'X');
  }

  ans = std::min(ans, solve(N, M, K, v));
  std::reverse(v.begin(), v.end());
  ans = std::min(ans, solve(N, M, N - K - 1, v));

  return ans;
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