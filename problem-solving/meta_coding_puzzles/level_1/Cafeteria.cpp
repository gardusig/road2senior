#include <bits/stdc++.h>
using namespace std;

long long getMaxAdditionalDinersCount(long long N, long long K, int M,
                                      vector<long long> S) {
  std::sort(S.begin(), S.end());

  long long ans = 0;
  ans += (S.front() - 1) / (K + 1);
  ans += (N - S.back()) / (K + 1);

  for (int i = 1; i < S.size(); i += 1) {
    long long available = S[i] - S[i - 1] - 1;
    if (available > K) {
      ans += (available - K) / (K + 1);
    }
  }

  return ans;
}
