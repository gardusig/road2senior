#include <bits/stdc++.h>

int exponentiate(int base, int power, const int MOD) {
  int ans = 1;
  while (power > 0) {
    if (power & 1) {
      ans = (1LL * ans * base) % MOD;
    }
    base = (1LL * base * base) % MOD;
    power >>= 1;
  }
  return ans;
}

std::vector<int> build_factorial(const int MAX_SIZE, const int MOD) {
  std::vector<int> fact(MAX_SIZE);
  fact[0] = 1;
  for (int i = 1; i < fact.size(); i += 1) {
    fact[i] = (1LL * fact[i - 1] * i) % MOD;
  }
  return fact;
}

std::vector<int> build_inverse_factorial(const std::vector<int>& fact,
                                         const int MOD) {
  std::vector<int> ifact(fact.size());
  ifact.back() = exponentiate(fact.back(), MOD - 2, MOD);
  for (int i = ifact.size() - 2; i >= 0; i -= 1) {
    ifact[i] = (1LL * (i + 1) * ifact[i + 1]) % MOD;
  }
  return ifact;
}

int combination(const int set_size, const int subset_size,
                const std::vector<int>& fat, const std::vector<int>& ifat,
                const int MOD) {
  if (subset_size < 0 or subset_size > set_size) {
    return 0;
  }
  const int num = fat[set_size];
  const int den =
      (1LL * ifat[set_size - subset_size] * ifat[subset_size]) % MOD;
  return (1LL * num * den) % MOD;
}

std::vector<int> get_lowest_factors(const int MAX_SIZE) {
  std::vector<int> lowest_factors(MAX_SIZE);
  for (int i = 0; i < lowest_factors.size(); i += 1) {
    lowest_factors[i] = (i & 1) ? i : 2;
  }
  for (int prime = 3; prime < lowest_factors.size(); prime += 2) {
    if (lowest_factors[prime] != prime) {
      continue;
    }
    for (int multiple = prime; multiple < lowest_factors.size();
         multiple += prime) {
      if (lowest_factors[multiple] != multiple) {
        continue;
      }
      lowest_factors[multiple] = prime;
    }
  }
  return lowest_factors;
}

std::unordered_map<int, int> get_factors(
    const int N, const std::vector<int>& lowest_factors) {
  std::unordered_map<int, int> factors;
  for (int i = N; i > 1; i /= lowest_factors[i]) {
    factors[lowest_factors[i]] += 1;
  }
  return factors;
}

// int count_divisors(const int N, const std::vector<int> &lowest_divisors) {
//   int ans = 1;
//   for (const auto &i : get_factors(N, lowest_divisors)) {
//     ans *= (i.second + 1);
//   }
//   return ans;
// }

// vector<vector<int> > combination_build(const auto &N, const auto &MOD) {
//   vector<vector<int> > v;
//   v.resize(N);
//   for (int i = 0; i < int(v.size()); ++i) v[i].resize(N);
//   for (int i = 0; i < N; ++i) {
//     v[i][0] = 1;
//     for (int j = 1; j < N; ++j) {
//       if (j > i)
//         v[i][j] = 0;
//       else
//         v[i][j] = (v[i - 1][j - 1] + v[i - 1][j]) % MOD;
//     }
//   }
//   return v;
// }

// int arithmetic_progression_element(const auto &value, const auto &pos_start,
//                                    const auto &pos_finish,
//                                    const auto &common_difference) {
//   return value + (pos_finish - pos_start) * common_difference;
// }

// int arithmetic_progression_sum(const auto &value_start,
//                                const auto &value_finish, const auto &n) {
//   return (n * (value_start + value_finish)) >> 1;
// }

// int geometric_progression_element(const auto &value, const auto &pos_start,
//                                   const auto &pos_finish,
//                                   const auto &common_ratio, const auto &MOD)
//                                   {
//   return value * exponentiate(common_ratio, pos_finish - pos_start, MOD);
// }

// int geometric_progression_sum(const auto &value, const auto &common_ratio,
//                               const auto &n) {
//   int num = value * (1 - pow(common_ratio, n));
//   int den = (1 - common_ratio);
//   return num / den;
// }
