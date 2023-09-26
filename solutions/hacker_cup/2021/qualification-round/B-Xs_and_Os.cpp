#include <bits/stdc++.h>

void solve_test_case(const int test) {
  int N;
  std::cin >> N;
  std::set<int> valid_rows;
  std::set<int> valid_columns;
  for (int i = 0; i < N; i += 1) {
    valid_rows.insert(i);
    valid_columns.insert(i);
  }
  std::vector<std::vector<int>> row_positions(N);
  std::vector<std::vector<int>> column_positions(N);
  for (int i = 0; i < N; i += 1) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < N; j += 1) {
      if (s[j] == '.') {
        row_positions[i].push_back(j);
        column_positions[j].push_back(i);
      } else if (s[j] == 'O') {
        valid_rows.erase(i);
        valid_columns.erase(j);
      }
    }
  }
  if (valid_rows.size() + valid_columns.size() == 0) {
    std::cout << "Case #" << test << ": "
              << "Impossible" << '\n';
    return;
  }
  int best = INT_MAX;
  for (const int row : valid_rows) {
    best = std::min(best, int(row_positions[row].size()));
  }
  for (const int column : valid_columns) {
    best = std::min(best, int(column_positions[column].size()));
  }
  std::set<std::vector<std::pair<int, int>>> ans;
  for (const int row : valid_rows) {
    if (best < row_positions[row].size()) {
      continue;
    }
    std::vector<std::pair<int, int>> positions;
    for (const int j : row_positions[row]) {
      positions.push_back({row, j});
    }
    ans.insert(positions);
  }
  for (const int column : valid_columns) {
    if (best < column_positions[column].size()) {
      continue;
    }
    std::vector<std::pair<int, int>> positions;
    for (const int i : column_positions[column]) {
      positions.push_back({i, column});
    }
    ans.insert(positions);
  }
  std::cout << "Case #" << test << ": " << best << " " << ans.size() << '\n';
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