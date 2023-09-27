#include <bits/stdc++.h>

class Math {
 public:
  void build_lowest_factors(const int size);
  std::unordered_map<int, int> get_factors(const int N) const;
  std::unordered_map<int64_t, int> get_factors_slow(int64_t N) const;
  std::vector<int> get_primes() const;

 private:
  std::vector<int> lowest_factors;
  std::vector<int> primes;
};

void Math::build_lowest_factors(const int size) {
  assert(size > 0);
  this->lowest_factors.resize(size);
  for (int i = 2; i < static_cast<int>(lowest_factors.size()); i += 1) {
    lowest_factors[i] = (i & 1) ? i : 2;
  }
  primes.push_back(2);
  for (int prime = 3; prime < static_cast<int>(lowest_factors.size());
       prime += 2) {
    if (lowest_factors[prime] != prime) {
      continue;
    }
    primes.push_back(prime);
    for (int multiple = prime;
         multiple < static_cast<int>(lowest_factors.size());
         multiple += prime) {
      if (lowest_factors[multiple] != multiple) {
        continue;
      }
      lowest_factors[multiple] = prime;
    }
  }
}

std::unordered_map<int, int> Math::get_factors(const int N) const {
  assert(N > 0);
  assert(N < static_cast<int>(lowest_factors.size()));
  std::unordered_map<int, int> factors;
  for (int i = N; i > 1; i /= lowest_factors[i]) {
    factors[lowest_factors[i]] += 1;
  }
  return factors;
}

std::unordered_map<int64_t, int> Math::get_factors_slow(int64_t N) const {
  assert(N > 0);
  std::unordered_map<int64_t, int> factors;
  for (const int prime : primes) {
    while (N % prime == 0) {
      factors[prime] += 1;
      N /= prime;
    }
    if (N == 1 || N < prime) {
      break;
    }
  }
  if (N > 1) {
    factors[N] += 1;
  }
  return factors;
}

std::vector<int> Math::get_primes() const { return this->primes; }
