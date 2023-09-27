//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MAX_SIZE = 100000 + 5;
const int SHIT_I_HATE_TLE = 10000000 + 5;

class FenTree {
  private:
    long long int v[MAX_SIZE];

  public:
    FenTree() {
      for (int i = 0; i < MAX_SIZE; i += 1) {
        v[i] = 0;
      }
    }

    void update(const int &idx, const long long int &value) {
      for (int i = idx; i < MAX_SIZE; i += i & -i) {
        v[i] += value;
      }
    }

    long long int query(const int &idx) {
      long long int ans = 0;
      for (int i = idx; i > 0; i -= i & -i) {
        ans += v[i];
      }
      return ans;
    }
};

class Node {
  public:
    int lo;
    int hi;
    int left;
    int right;
    int value;
    int mid;

    Node() {}

    Node(const int &lo, const int &hi) {
      this->lo = lo;
      this->hi = hi;
      this->mid = this->lo + ((this->hi - this->lo) >> 1);
      this->value = 0;
      this->left = -1;
      this->right = -1;
    }
};

class Solution {
  private:
    int T;
    int N;
    int A[4];
    int version;
    int nxt_node;
    int sz[MAX_SIZE];
    int have_less[MAX_SIZE];
    int have_greater[MAX_SIZE];
    int sum_have_less[MAX_SIZE];
    int sum_have_greater[MAX_SIZE];
    vector< int > g[MAX_SIZE];
    Node frequency[SHIT_I_HATE_TLE];

    void build(Node &root) {
      if (root.lo == root.hi) {
        return;
      }
      root.left = nxt_node++;
      frequency[root.left] = Node(root.lo, root.mid);
      build(frequency[root.left]);
      root.right = nxt_node++;
      frequency[root.right] = Node(root.mid + 1, root.hi);
      build(frequency[root.right]);
    }

    void update(Node &kappa, const Node &keepo, const int &idx, const int &value) {
      if (kappa.lo == idx and kappa.hi == idx) {
        kappa.value = value;
        return;
      }
      if (idx <= kappa.mid) {
        kappa.right = keepo.right;
        kappa.left = nxt_node++;
        frequency[kappa.left] = Node(kappa.lo, kappa.mid);
        update(frequency[kappa.left], frequency[keepo.left], idx, value);
      } else {
        kappa.left = keepo.left;
        kappa.right = nxt_node++;
        frequency[kappa.right] = Node(kappa.mid + 1, kappa.hi);
        update(frequency[kappa.right], frequency[keepo.right], idx, value);
      }
      kappa.value = frequency[kappa.left].value + frequency[kappa.right].value;
    }

    int query(const Node &root, const int &lo, const int &hi) {
      if (root.lo >= lo and root.hi <= hi) {
        return root.value;
      }
      int ans = 0;
      if (lo <= root.mid) {
        ans += query(frequency[root.left], lo, hi);
      }
      if (hi > root.mid) {
        ans += query(frequency[root.right], lo, hi);
      }
      return ans;
    }

    void dfs_build(const int &i, const int &p) {
      sz[i] = 1;
      for (const int &j: g[i]) {
        if (j == p) {
          continue;
        }
        dfs_build(j, i);
        sz[i] += sz[j];
      }
      version += 1;
      frequency[version] = Node(1, MAX_SIZE);
      update(frequency[version], frequency[version - 1], i, 1);
      have_less[i] = query(frequency[version], 1, p - 1) - query(frequency[version - sz[i]], 1, p - 1);
      have_greater[i] = sz[i] - have_less[i];
      sum_have_less[p] += have_less[i];
      sum_have_greater[p] += have_greater[i];
    }

    long long int dfs_solve(const int &i, const int &p) {
      long long int ans = 0;
      for (const int &j: g[i]) {
        if (j == p) {
          if (A[2] == 1) {
            const int &l = sum_have_greater[i];
            const int &r = (N - i) - l;
            ans += 1LL * l * r;
          }
          else if (A[2] == 2) {
            ans += 1LL * sum_have_less[i] * (N - i - sum_have_greater[i]);
            ans += 1LL * sum_have_greater[i] * (i - 1 - sum_have_less[i]);
          } else if (A[2] == 3) {
            const int &l = sum_have_less[i];
            const int &r = (i - 1) - l;
            ans += 1LL * l * r;
          }
        }
        else {
          ans += dfs_solve(j, i);
          if (A[2] == 1) {
            const int &l = have_greater[j];
            const int &r = (N - i) - l;
            ans += 1LL * l * r;
          }
          else if (A[2] == 2) {
            ans += 1LL * have_less[j] * (N - i - have_greater[j]);
            ans += 1LL * have_greater[j] * (i - 1 - have_less[j]);
          } else if (A[2] == 3) {
            const int &l = have_less[j];
            const int &r = (i - 1) - l;
            ans += 1LL * l * r;
          }
        }
      }
      return ans;
    }

    long long int solve() {
      int root = 0;
      for (int i = 1; i <= N; i += 1) {
        if (int(g[i].size()) == 1) {
          root = i;
          break;
        }
      }
      dfs_build(root, 0);
      return dfs_solve(root, 0) >> 1;
    }

    void scanint(int &x) {
      x = 0;
      register int c = getchar_unlocked();
      for (; c < '0' or c > '9'; c = getchar_unlocked());
      for (; c >= '0' and c <= '9'; c = getchar_unlocked()) {
        x = (x << 1) + (x << 3) + c - 48;
      }
    }

    long long int trash(const vector< int > &v) {
      long long int ans = 0;
      FenTree dp = FenTree();
      FenTree have = FenTree();
      for (const int &i: v) {
        have.update(i, 1);
        if (A[2] > A[1]) {
          dp.update(i, have.query(i - 1));
        } else {
          dp.update(i, have.query(N) - have.query(i));
        }
        if (A[3] > A[2]) {
          ans += dp.query(i - 1);
        } else {
          ans += dp.query(N) - dp.query(i);
        }
      }
      return ans;
    }

    void dfs_3(const int &i, const int &p, vector< int > &v) {
      for (const int &j: g[i]) {
        if (j == p) {
          continue;
        }
        dfs_3(j, i, v);
      }
      v.push_back(i);
    }

    long long int solve_3() {
      int root = 0;
      for (int i = 1; i <= N; i += 1) {
        if (int(g[i].size()) == 1) {
          root = i;
          break;
        }
      }
      vector< int > v;
      dfs_3(root, -1, v);
      long long int ans = 0;
      ans += trash(v);
      if (A[2] == 2) {
        swap(A[1], A[3]);
        ans += trash(v);
      }
      return ans;
    }

    long long int check() {
      vector< int > qtd(MAX_SIZE, 0);
      for (int i = 1; i <= N; i += 1) {
        qtd[int(g[i].size())] += 1;
      }
      if (qtd[2] == N - 2 and qtd[1] == 2) {
        return solve_3();
      }
      return solve();
    }

  public:
    Solution() {
      nxt_node = MAX_SIZE + 1;
      frequency[0] = Node(1, MAX_SIZE);
      build(frequency[0]);
      const int backup = nxt_node;
      scanint(T);
      while (T-- > 0) {
        scanint(N);
        for (int i = 1; i <= 3; i += 1) {
          scanint(A[i]);
        }
        for (int i = 1; i <= N; i += 1) {
          g[i].clear();
          sum_have_less[i] = 0;
          sum_have_greater[i] = 0;
        }
        for (int i = 1; i < N; i += 1) {
          int x, y;
          scanint(x);
          scanint(y);
          g[x].push_back(y);
          g[y].push_back(x);
        }
        version = 0;
        nxt_node = backup;
        printf("%lld\n", check());
      }
    }
};

int main() {
  Solution();
  return 0;
}