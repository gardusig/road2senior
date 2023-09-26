#include <bits/stdc++.h>

const int MAX_SIZE = 51;

int N;
int C[MAX_SIZE];
std::vector<int> g[MAX_SIZE];
int64_t dp[MAX_SIZE][MAX_SIZE];

int64_t solve(const int i, const int p, const int moves) {
  if (dp[i][moves] != -1) {
    return dp[i][moves];
  }
  std::map<int, std::vector<int64_t>> possibilities;
  for (const int j : g[i]) {
    if (j == p) {
      continue;
    }
    for (int k = 0; k <= moves; k += 1) {
      possibilities[k].push_back(solve(j, i, k));
    }
  }
  for (int k = 0; k <= moves; k += 1) {
    auto& v = possibilities[std::max(0, k - 1)];
    std::sort(v.rbegin(), v.rend());
    dp[i][k] = C[i];
    for (int j = 0; j <= std::min(k, int(v.size()) - 1); j += 1) {
      dp[i][k] += v[j];
    }
  }
  return dp[i][moves];
}

void solve_test_case(const int test) {
  std::cin >> N;
  for (int i = 0; i < N; i += 1) {
    std::cin >> C[i];
  }
  for (int i = 0; i < N; i += 1) {
    g[i].clear();
  }
  for (int i = 1; i < N; i += 1) {
    int x, y;
    std::cin >> x >> y;
    x -= 1;
    y -= 1;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::memset(dp, -1, sizeof dp);
  std::cout << "Case #" << test << ": " << solve(0, 0, 1) << '\n';
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