#include <bits/stdc++.h>
using namespace std;

int countPhotographs(int N, string C, int X, int Y) {
  int ans = 0;
  for (int i = 0; i < N; i += 1) {
    if (C[i] != 'P') {
      continue;
    }
    for (int j = i + X; j < N and j - i <= Y; j += 1) {
      if (C[j] != 'A') {
        continue;
      }
      for (int k = j + X; k < N and k - j <= Y; k += 1) {
        if (C[k] != 'B') {
          continue;
        }
        ans += 1;
      }
    }
  }
  return ans;
}

int getArtisticPhotographCount(int N, string C, int X, int Y) {
  int ans = 0;
  ans += countPhotographs(N, C, X, Y);
  std::reverse(C.begin(), C.end());
  ans += countPhotographs(N, C, X, Y);
  return ans;
}
