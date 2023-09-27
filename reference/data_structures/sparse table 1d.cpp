vector< vector< int > > build_sparse_table(const auto &v) {
  int n = int(v.size());
  int m = log2(n) + 1;
  vector< vector< int > > st(n, vector< int >(m));
  for (int i = 0; i < n; i += 1) {
    st[i][0] = v[i];
  }
  for (int j = 1; j < m; j += 1) {
    for (int i = 0; i + (1 << (j - 1)) < n; i += 1) {
      st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
    }
  }
  return st;
}

int query(const auto &l, const auto &r, const auto &st) {
  int diff = r - l + 1;
  int pot = 31 - __builtin_clz(diff);
  int a = st[l][pot];
  int b = st[l + diff - (1 << pot)][pot];
  return a | b;
}