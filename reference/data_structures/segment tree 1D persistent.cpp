//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

const int MAX_SIZE = 100000 + 1;

class Node {
  private:
    int lo;
    int hi;
    Node* left;
    Node* right;
    int value;
    int mid;

  public:
    Node(const int &lo, const int &hi) {
      this->lo = lo;
      this->hi = hi;
      this->value = 0;
      this->mid = this->lo + ((this->hi - this->lo) >> 1);
    }

    void build() {
      if (this->lo == this->hi) {
        return;
      }
      this->left = new Node(this->lo, this->mid);
      this->left->build();
      this->right = new Node(this->mid + 1, this->hi);
      this->right->build();
    }

    void update(Node* const &other, const int &idx, const int &new_value) {
      if (this->lo == idx and this->hi == idx) {
        this->value = new_value;
        return;
      }
      if (idx <= other->mid) {
        this->right = other->right;
        this->left = new Node(this->lo, this->mid);
        this->left->update(other->left, idx, new_value);
      } else {
        this->left = other->left;
        this->right = new Node(this->mid + 1, this->hi);
        this->right->update(other->right, idx, new_value);
      }
      this->value = this->left->value + this->right->value;
    }

    int query(const int &lo, const int &hi) {
      if (this->lo > hi or this->hi < lo) {
        return 0LL;
      }
      if (this->lo >= lo and this->hi <= hi) {
        return this->value;
      }
      return this->left->query(lo, hi) + this->right->query(lo, hi);
    }
};

class Solution {
  private:
    int T;
    int N;
    int A[4];
    int version;
    int sz[MAX_SIZE];
    vector< int > g[MAX_SIZE];
    Node* frequency[MAX_SIZE];
    int frequency_version[MAX_SIZE];

    long long int dfs_solve(const int &i, const int &p) {
      sz[i] = 1;
      long long int ans = 0;
      for (const int &j: g[i]) {
        if (j == p) {
          continue;
        }
        ans += dfs_solve(j, i);
        sz[i] += sz[j];
      }
      version += 1;
      frequency_version[i] = version;
      frequency[version] = new Node(1, MAX_SIZE);
      frequency[version]->update(frequency[version - 1], i, 1);
      int l, r;
      for (const int &j: g[i]) {
        int r_version = (j == p) ? frequency_version[i] : frequency_version[j];
        int l_version = r_version - sz[(j == p) ? i : j];
        if (A[2] == 1) {
          l = frequency[r_version]->query(i + 1, N) - frequency[l_version]->query(i + 1, N);
          r = N - i - l;
          ans += 1LL * l * r;
        }
        else if (A[2] == 2) {
          l = frequency[r_version]->query(1, i - 1) - frequency[l_version]->query(1, i - 1);
          r = N - i - (frequency[r_version]->query(i + 1, N) - frequency[l_version]->query(i + 1, N));
          ans += 1LL * l * r;
          l = frequency[r_version]->query(i + 1, N) - frequency[l_version]->query(i + 1, N);
          r = i - 1 - (frequency[r_version]->query(1, i - 1) - frequency[l_version]->query(1, i - 1));
          ans += 1LL * l * r;
        } else if (A[2] == 3) {
          l = frequency[r_version]->query(1, i - 1) - frequency[l_version]->query(1, i - 1);
          r = i - 1 - l;
          ans += 1LL * l * r;
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
      version = 0;
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

  public:
    Solution() {
      frequency[0] = new Node(1, MAX_SIZE);
      frequency[0]->build();
      scanint(T);
      while (T-- > 0) {
        scanint(N);
        for (int i = 1; i <= 3; i += 1) {
          scanint(A[i]);
        }
        for (int i = 1; i <= N; i += 1) {
          g[i].clear();
        }
        for (int i = 1; i < N; i += 1) {
          int x, y;
          scanint(x);
          scanint(y);
          g[x].push_back(y);
          g[y].push_back(x);
        }
        printf("%lld\n", solve());
      }
    }
};

int main() {
  Solution();
  return 0;
}
