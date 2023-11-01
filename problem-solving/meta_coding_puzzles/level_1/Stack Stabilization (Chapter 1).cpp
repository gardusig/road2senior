#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getMinimumDeflatedDiscCount(int N, vector<int> R) {
  int ans = 0;
  int last = R.back();
  for (int i = N - 2; i >= 0; i -= 1) {
    if (R[i] >= last) {
      ans += 1;
      last = last - 1;
    } else {
      last = R[i];
    }
    if (last < 1) {
      return -1;
    }
  }
  return ans;
}
