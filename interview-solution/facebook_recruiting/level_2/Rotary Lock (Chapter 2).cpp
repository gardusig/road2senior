#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int get_best_movement(const int x, const int y, const int N) {
  const int mn = std::min(x, y);
  const int mx = std::max(x, y);
  return std::min(mx - mn, mn + N - mx);
}

std::unordered_map<int, std::unordered_map<int, long long>> dp;

long long solve(const int N, const int x, const int y,
                const std::vector<int>& values) {
  const int current_pos = std::max(x, y) + 1;
  if (current_pos == int(values.size())) {
    return 0;
  }
  if (dp.count(x) and dp[x].count(y)) {
    return dp[x][y];
  }
  long long move_x = solve(N, current_pos, y, values) +
                     get_best_movement(values[x], values[current_pos], N);
  long long move_y = solve(N, x, current_pos, values) +
                     get_best_movement(values[y], values[current_pos], N);
  dp[x][y] = std::min(move_x, move_y);
  return dp[x][y];
}

long long getMinCodeEntryTime(int N, int M, vector<int> C) {
  std::vector<int> values;
  values.push_back(1);
  for (const int c : C) {
    values.push_back(c);
  }
  dp.clear();
  return solve(N, 0, 0, values);
}
