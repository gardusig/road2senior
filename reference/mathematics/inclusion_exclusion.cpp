#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 512345;

vector<int> build_lowest_factor() {
  vector<int> lowest_factor(MAX_SIZE);
  for (int i = 0; i < int(lowest_factor.size()); i += 1) lowest_factor[i] = i;
  for (int i = 2; i < int(lowest_factor.size()); i += 1)
    if (lowest_factor[i] == i)
      for (int j = i + i; j < int(lowest_factor.size()); j += i)
        if (lowest_factor[j] == j) lowest_factor[j] = i;
  return lowest_factor;
}

vector<set<int> > build_factors() {
  auto lowest_factor = build_lowest_factor();
  vector<set<int> > factors(MAX_SIZE);
  for (int i = 2; i < int(factors.size()); i += 1)
    for (int j = i; j > 1; j /= lowest_factor[j])
      factors[i].insert(lowest_factor[j]);
  return factors;
}

void update(const auto &number, const auto &change, const auto &factors,
            auto &have, auto &elements) {
  elements += change;
  for (int mask = 1; mask < (1 << int(factors[number].size())); mask += 1) {
    int value = 1, pot = 1;
    for (const auto &i : factors[number]) {
      if ((mask & pot) != 0) value *= i;
      pot <<= 1;
    }
    have[value] += change;
  }
}

int query(const auto &number, const auto &factors, const auto &have) {
  int edges = 0;
  for (int mask = 1; mask < (1 << int(factors[number].size())); mask += 1) {
    int value = 1, qtd = 0, pot = 1;
    for (const auto &i : factors[number]) {
      if ((mask & pot) != 0) qtd += 1, value *= i;
      pot <<= 1;
    }
    if ((qtd & 1) != 0)
      edges += have[value];
    else
      edges -= have[value];
  }
  return edges;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  auto factors = build_factors();
  vector<int> have(MAX_SIZE, 0);
  vector<bool> stock(MAX_SIZE, false);
  int n, t;
  cin >> n >> t;
  vector<int> id(n);
  for (int i = 0; i < n; i += 1) cin >> id[i];
  long long int ans = 0, elements = 0;
  while (t-- > 0) {
    int pos;
    cin >> pos;
    pos -= 1;
    if (stock[pos] == true) update(id[pos], -1, factors, have, elements);
    int change = elements - query(id[pos], factors, have);
    if (stock[pos] == true)
      ans -= change;
    else
      update(id[pos], +1, factors, have, elements), ans += change;
    stock[pos] = !stock[pos];
    cout << ans << '\n';
  }
  return 0;
}