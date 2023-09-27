#include <bits/stdc++.h>

int N, Q;
std::vector<int> A;
int BLOCK_SIZE;
int CURRENT_ANSWER;
std::vector<int> frequency;
std::vector<int> numbers_with_frequency;

bool cmp(const std::pair<std::pair<int, int>, int>& a,
         const std::pair<std::pair<int, int>, int>& b) {
  const int value_a = a.first.first / BLOCK_SIZE;
  const int value_b = b.first.first / BLOCK_SIZE;
  if (value_a == value_b) {
    return (value_a & 1) ? (a.first.second < b.first.second)
                         : (a.first.second > b.first.second);
  }
  return value_a < value_b;
}

void build(std::vector<std::pair<std::pair<int, int>, int>>& queries) {
  CURRENT_ANSWER = 0;
  for (int i = 0; 1LL * i * i <= A.size(); i += 1) {
    BLOCK_SIZE = i;
  }
  std::vector<int> compressed = A;
  std::sort(compressed.begin(), compressed.end());
  frequency = std::vector<int>(A.size() + 1, 0);
  numbers_with_frequency = std::vector<int>(A.size(), 0);
  for (int i = 0; i < A.size(); i += 1) {
    A[i] = std::lower_bound(compressed.begin(), compressed.end(), A[i]) -
           compressed.begin();
    frequency[A[i]] = 0;
    numbers_with_frequency[frequency[A[i]]] += 1;
  }
  std::sort(queries.begin(), queries.end(), cmp);
}

void add(const int idx) {
  const int value = A[idx];
  numbers_with_frequency[frequency[value]] -= 1;
  frequency[value] += 1;
  numbers_with_frequency[frequency[value]] += 1;
  CURRENT_ANSWER = std::max(CURRENT_ANSWER, frequency[value]);
}

void remove(const int idx) {
  const int value = A[idx];
  numbers_with_frequency[frequency[value]] -= 1;
  frequency[value] -= 1;
  numbers_with_frequency[frequency[value]] += 1;
  while (numbers_with_frequency[CURRENT_ANSWER] == 0) {
    CURRENT_ANSWER -= 1;
  }
}

void process_L(int& idx, const int query_idx) {
  while (idx > query_idx) {
    idx -= 1;
    add(idx);
  }
  while (idx < query_idx) {
    remove(idx);
    idx += 1;
  }
}

void process_R(int& idx, const int query_idx) {
  while (idx < query_idx) {
    idx += 1;
    add(idx);
  }
  while (idx > query_idx) {
    remove(idx);
    idx -= 1;
  }
}

std::vector<int> solve(
    std::vector<std::pair<std::pair<int, int>, int>>& queries) {
  build(queries);
  std::vector<int> answer(Q);
  int L = 0;
  int R = -1;
  for (const auto& query : queries) {
    const int query_ID = query.second;
    const int query_L = query.first.first;
    const int query_R = query.first.second;
    process_L(L, query_L);
    process_R(R, query_R);
    answer[query_ID] = CURRENT_ANSWER;
  }
  return answer;
}

int main() {
  scanf("%d %d", &N, &Q);
  A.resize(N);
  for (int i = 0; i < N; i += 1) {
    scanf("%d", &A[i]);
  }
  std::vector<std::pair<std::pair<int, int>, int>> queries;
  for (int i = 0; i < Q; i += 1) {
    int L, R;
    scanf("%d %d", &L, &R);
    L -= 1;
    R -= 1;
    queries.push_back({{L, R}, i});
  }
  for (const int answer : solve(queries)) {
    printf("%d\n", answer);
  }
  return 0;
}