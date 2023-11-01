#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

double getHitProbability(int R, int C, vector<vector<int>> G) {
  int allPossibleWays = R * C;
  int correctWays = 0;
  for (const auto& row : G) {
    for (const int colum : row) {
      if (colum == 1) {
        correctWays += 1;
      }
    }
  }
  return double(correctWays) / double(allPossibleWays);
}
