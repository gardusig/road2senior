#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getUniformIntegerCountInInterval(long long A, long long B) {
  int answer = 0;
  for (int digit = 1; digit <= 9; digit += 1) {
    long long number = 0;
    for (int length = 1; length <= 13; length += 1) {
      number *= 10;
      number += digit;
      if (number > B) {
        break;
      }
      if (number >= A) {
        answer += 1;
      }
    }
  }
  return answer;
}
