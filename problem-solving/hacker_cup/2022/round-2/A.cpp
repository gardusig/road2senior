#include <bits/stdc++.h>

std::vector<std::map<char, int>> get_frequency(const std::string& s) {
  std::vector<std::map<char, int>> ans;
  std::map<char, int> current;
  ans.push_back(current);
  for (const char c : s) {
    current[c] += 1;
    ans.push_back(current);
  }
  return ans;
}

std::map<char, int> get_interval_frequency(
    const int L, const int R, std::vector<std::map<char, int>>& v) {
  std::map<char, int> f;
  for (auto& i : v[R]) {
    f[i.first] += i.second;
  }
  for (auto& i : v[L - 1]) {
    f[i.first] -= i.second;
  }
  return f;
}

bool is_palindrome(std::map<char, int>& frequency_with_addition,
                   std::map<char, int>& frequency) {
  std::set<char> keys;
  for (const auto& i : frequency_with_addition) {
    keys.insert(i.first);
  }
  for (const auto& i : frequency) {
    keys.insert(i.first);
  }
  bool has_removed = false;
  for (const char key : keys) {
    const int diff = abs(frequency[key] - frequency_with_addition[key]);
    if (diff == 0) {
      continue;
    }
    if (diff > 1) {
      return false;
    }
    if (has_removed) {
      return false;
    }
    has_removed = true;
  }
  return has_removed;
}

void solve_test_case(const int test) {
  std::string s;
  std::cin >> s;
  int Q;
  std::cin >> Q;
  int ans = 0;
  std::vector<std::map<char, int>> accum_frequency = get_frequency(s);
  for (int q = 0; q < Q; q += 1) {
    int L, R;
    std::cin >> L >> R;
    if (((R - L) & 1)) {
      continue;
    }
    bool is_valid = false;
    const int mid = (L + R) / 2;
    std::map<char, int> first_half;
    std::map<char, int> second_half;
    first_half = get_interval_frequency(L, mid, accum_frequency);
    second_half = get_interval_frequency(mid + 1, R, accum_frequency);
    if (is_palindrome(first_half, second_half)) {
      is_valid = true;
    }
    first_half = get_interval_frequency(mid, R, accum_frequency);
    second_half = get_interval_frequency(L, mid - 1, accum_frequency);
    if (is_palindrome(first_half, second_half)) {
      is_valid = true;
    }
    if (is_valid) {
      ans += 1;
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
