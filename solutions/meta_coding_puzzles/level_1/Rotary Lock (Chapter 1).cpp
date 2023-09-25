#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

long long getMinCodeEntryTime(int N, int M, vector<int> C) {
  long long ans = 0;
  int last_position = 1;
  for (const int c : C) {
    const int mn = std::min(last_position, c);
    const int mx = std::max(last_position, c);
    int current_cost = std::min(mx - mn, mn + N - mx);
    ans += current_cost;
    last_position = c;
  }
  return ans;
}
