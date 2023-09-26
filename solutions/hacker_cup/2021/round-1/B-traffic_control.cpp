#include <bits/stdc++.h>

int N, M, A, B;
int v[51][51];

void solve_test_case(const int test) {
  std::cin >> N >> M >> A >> B;

  const int remove = N + M - 2;

  std::cout << "Case #" << test << ": ";

  if (remove >= std::min(A, B)) {
    std::cout << "Impossible" << std::endl;
    return;
  }

  for (int i = 0; i < N; i += 1) {
    for (int j = 0; j < M; j += 1) {
      v[i][j] = 1;
    }
  }

  v[0][0] = A - remove;
  v[0][M - 1] = B - remove;

  std::cout << "Possible" << std::endl;
  for (int i = 0; i < N; i += 1) {
    for (int j = 0; j < M; j += 1) {
      std::cout << v[i][j] << (j == M - 1 ? '\n' : ' ');
    }
  }
}

int32_t main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}