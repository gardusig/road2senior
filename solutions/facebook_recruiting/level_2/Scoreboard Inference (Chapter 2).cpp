#include <bits/stdc++.h>
using namespace std;

bool can_get_score(const int score, const int qty_one, const int qty_two,
                   const int qty_three) {
  for (int used_one = 0; used_one <= qty_one; used_one += 1) {
    for (int used_two = 0; used_two <= qty_two; used_two += 1) {
      const int to_remove = 1 * used_one + 2 * used_two;
      if (score < to_remove) {
        continue;
      }
      const int remaining = score - to_remove;
      if (remaining % 3) {
        continue;
      }
      if (remaining / 3 > qty_three) {
        continue;
      }
      return true;
    }
  }
  return false;
}

bool is_competition_possible(const vector<int> &v, const int qty_one,
                             const int qty_two, const int qty_three) {
  for (const int score : v) {
    if (!can_get_score(score, qty_one, qty_two, qty_three)) {
      return false;
    }
  }
  return true;
}

int getMinProblemCount(int N, vector<int> S) {
  int answer = INT_MAX;
  const int max_element = *std::max_element(S.begin(), S.end());
  const int mn = std::max(0, (max_element / 3) - 2);
  for (int qty_one = 0; qty_one <= 1; qty_one += 1) {
    for (int qty_two = 0; qty_two <= 2; qty_two += 1) {
      for (int qty_three = mn; qty_three <= mn + 5; qty_three += 1) {
        if (is_competition_possible(S, qty_one, qty_two, qty_three)) {
          answer = std::min(answer, qty_one + qty_two + qty_three);
        }
      }
    }
  }
  return answer;
}
