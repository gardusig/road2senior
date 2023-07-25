#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getMinProblemCount(int N, vector<int> S) {
  bool hasOdd = false;
  int minimumEven = 0;
  for (const int i : S) {
    hasOdd |= (i & 1);
    minimumEven = std::max(minimumEven, i >> 1);
  }
  return minimumEven + hasOdd;
}
