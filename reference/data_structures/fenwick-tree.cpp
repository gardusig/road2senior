#include <bits/stdc++.h>

template <typename T>
class FenwickTree {
 public:
  explicit FenwickTree(const int size) : accum(size, 0) {}

  void clear() { std::fill(accum.begin(), accum.end(), 0); }

  void resize(const int size) {
    if (size < 0) {
      assert(false);
    }
    this->accum.resize(size);
  }

  T query(const int idx) const {
    if (idx >= static_cast<int>(this->accum.size())) {
      assert(false);
    }
    T ans = 0;
    for (int i = idx; i > 0; i -= i & (-i)) {
      ans += this->accum[i];
    }
    return ans;
  }

  void update(const int idx, const T value) {
    if (idx <= 0) {
      assert(false);
    }
    if (idx >= static_cast<int>(accum.size())) {
      assert(false);
    }
    for (int i = idx; i < static_cast<int>(accum.size()); i += i & (-i)) {
      this->accum[i] += value;
    }
  }

 private:
  std::vector<T> accum;
};
