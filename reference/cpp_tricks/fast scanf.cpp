#include <bits/stdc++.h>

int read_integer() {
  int N = 0;
  register int c = '$';
  while (!isdigit(c)) {
    c = getchar_unlocked();
  }
  while (isdigit(c)) {
    N = (N << 1) + (N << 3) + c - '0';
    c = getchar_unlocked();
  }
  return N;
}
