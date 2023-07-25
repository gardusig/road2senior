#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

char getOppositeChar(const char c) { return c == 'A' ? 'B' : 'A'; }

string getWrongAnswers(int N, string C) {
  std::string answer = "";
  for (const int c : C) {
    answer.push_back(getOppositeChar(c));
  }
  return answer;
}
