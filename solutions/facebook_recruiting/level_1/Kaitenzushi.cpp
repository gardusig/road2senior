#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

int getMaximumEatenDishCount(int N, vector<int> D, int K) {
  int total_eaten = 0;
  std::queue<int> to_remove_queue;
  std::set<int> eaten_dishes;
  for (int i = 0; i < N; i += 1) {
    if (eaten_dishes.count(D[i]) == 0) {
      total_eaten += 1;
      eaten_dishes.insert(D[i]);
      to_remove_queue.push(D[i]);
    }
    while (to_remove_queue.size() > K) {
      eaten_dishes.erase(to_remove_queue.front());
      to_remove_queue.pop();
    }
  }
  return total_eaten;
}
