#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

const int STRING_MAX_SIZE = 1'000'000 + 5;
const int ALPHABET_MAX_SIZE = 26;

int charFrequency[STRING_MAX_SIZE][ALPHABET_MAX_SIZE];

void buildCharFrequencyFromString(const int N, const std::string& s) {
  for (int i = 0; i < N; i += 1) {
    for (int j = 0; j < ALPHABET_MAX_SIZE; j += 1) {
      charFrequency[i][j] = (i > 0) ? charFrequency[i - 1][j] : 0;
    }
    charFrequency[i][s[i] - 'A'] += 1;
  }
}

int getCharFrequency(const int N, int L, int R, const char C) {
  if (R < 0 or L >= N or L > R) {
    return 0;
  }
  R = std::min(R, N - 1);
  int ans = charFrequency[R][C - 'A'];
  if (L > 0) {
    ans -= charFrequency[L - 1][C - 'A'];
  }
  return ans;
}

long long countPhotographs(int N, string C, int X, int Y) {
  buildCharFrequencyFromString(N, C);
  long long ans = 0;
  for (int i = 0; i < N; i += 1) {
    if (C[i] != 'A') {
      continue;
    }
    const int validPhotographersBefore = getCharFrequency(N, i - Y, i - X, 'P');
    const int validBackdropsAfter = getCharFrequency(N, i + X, i + Y, 'B');
    ans += 1LL * validPhotographersBefore * validBackdropsAfter;
  }
  return ans;
}

long long getArtisticPhotographCount(int N, string C, int X, int Y) {
  long long ans = 0;
  ans += countPhotographs(N, C, X, Y);
  std::reverse(C.begin(), C.end());
  ans += countPhotographs(N, C, X, Y);
  return ans;
}
