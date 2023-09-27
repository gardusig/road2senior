#include <bits/stdc++.h>

class Solution
{
public:
  Solution()
  {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
  }

  void main()
  {
    std::cin >> T;
    for (int test = 1; test <= T; test += 1)
    {
      std::cin >> N >> H;
      A.resize(N);
      for (int& i : A)
      {
        std::cin >> i;
      }
      B.resize(N);
      for (int& i : B)
      {
        std::cin >> i;
      }
      std::cout << "Case #" << test << ": " << solve() << std::endl;
    }
  }

private:
  int T;
  int N;
  int H;
  std::vector< int > A;
  std::vector< int > B;

  long long int solve()
  {
    std::vector< bool > validA(1 << N, false);
    std::vector< bool > validB(1 << N, false);
    for (int mask = 0; mask < (1 << N); mask += 1)
    {
      long long int currentA = 0;
      long long int currentB = 0;
      for (int i = 0; i < N; i += 1)
      {
        if (mask & (1 << i))
        {
          currentA += A[i];
          currentB += B[i];
        }
      }
      if (currentA >= H)
      {
        validA[mask] = true;
      }
      if (currentB >= H)
      {
        validB[mask] = true;
      }
    }
    std::vector< long long int > dp(1 << N, 0);
    for (int mask = 0; mask < (1 << N); mask += 1)
    {
      dp[mask] = validB[mask];
    }
    for (int i = 0; i < N; i += 1)
    {
      for (int mask = 0; mask < (1 << N); mask += 1)
      {
        if (mask & (1 << i))
        {
          dp[mask ^ (1 << i)] += dp[mask];
        }
      }
    }
    long long int ans = 0;
    for (int mask = 0; mask < (1 << N); mask += 1)
    {
      if (validA[mask] == true)
      {
        ans += dp[((1 << N) - 1) ^ mask];
      }
    }
    return ans;
  }
};

int main()
{
  Solution().main();
  return 0;
}