#include <bits/stdc++.h>

const int MAX_SIZE = 800000 + 5;
const int MAX_SIZE_LOG = 20;

std::vector<int> g[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE_LOG];
int depth[MAX_SIZE];
int64_t accum[MAX_SIZE];

void reset(const int N) {
  for (int i = 0; i < MAX_SIZE; i += 1) {
    g[i].clear();
    accum[i] = 0;
  }
}

void dfs(const int i, const int p) {
  depth[i] = depth[p] + 1;
  dp[i][0] = p;
  for (int j = 1; j < MAX_SIZE_LOG; j += 1) {
    dp[i][j] = dp[dp[i][j - 1]][j - 1];
  }
  for (const int nxt : g[i]) {
    if (nxt == p) {
      continue;
    }
    dfs(nxt, i);
  }
}

int get_lca(int x, int y) {
  if (depth[x] < depth[y]) {
    std::swap(x, y);
  }
  const int diff = depth[x] - depth[y];
  for (int j = 0; j < MAX_SIZE_LOG; j += 1) {
    if (diff & (1 << j)) {
      x = dp[x][j];
    }
  }
  if (x == y) {
    return x;
  }
  for (int j = MAX_SIZE_LOG - 1; j >= 0; j -= 1) {
    if (dp[x][j] != dp[y][j]) {
      x = dp[x][j];
      y = dp[y][j];
    }
  }
  return dp[x][0];
}

int solve(const int i, const int p) {
  int ans = 0;
  for (const int j : g[i]) {
    if (j == p) {
      continue;
    }
    ans += solve(j, i);
    accum[i] += accum[j];
    if (accum[j] == 0) {
      ans += 1;
    }
  }
  return ans;
}

int solve_test_case() {
  int N;
  std::cin >> N;
  reset(N);
  std::map<int, std::vector<int>> f;
  for (int i = 1; i < N; i += 1) {
    int X, Y;
    std::cin >> X >> Y;
    X -= 1;
    Y -= 1;
    g[X].push_back(Y);
    g[Y].push_back(X);
  }
  depth[0] = 0;
  dfs(0, 0);
  for (int i = 0; i < N; i += 1) {
    int value;
    std::cin >> value;
    f[value].push_back(i);
  }
  for (const auto& it : f) {
    const auto& values = it.second;
    if (values.size() == 1) {
      continue;
    }
    int lca = values[0];
    for (const int i : values) {
      lca = get_lca(lca, i);
      accum[i] += 1;
    }
    accum[lca] -= values.size();
  }
  return solve(0, 0);
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    std::cout << "Case #" << test << ": " << solve_test_case() << std::endl;
  }
  return 0;
}