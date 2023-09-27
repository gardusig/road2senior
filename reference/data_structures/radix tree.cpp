#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 1123456;

class trie_node {
public:
    int jump, edges;
    vector<int> indexes;
    vector<trie_node*> nxt;
    trie_node() {
        this->jump = 1;
        this->edges = 0;
        this->nxt = vector<trie_node*>(2, NULL);
    }
    void build_radix_tree() {
        for (int i = 0; i < 2; ++i) {
            if (this->nxt[i] == NULL)
                continue;
            this->nxt[i]->build_radix_tree();
            if (this->edges < 2) {
                this->jump += this->nxt[i]->jump;
                this->edges = this->nxt[i]->edges;
                auto trash = this->nxt[i];
                this->nxt = this->nxt[i]->nxt;
                delete(trash);
            }
        }
    }
    void insert_custom(const auto &i, const auto &s, const auto &idx) {
        this->indexes.push_back(idx);
        if (i == int(s.size()))
            return;
        int j = (s[i] - '0');
        this->nxt[j]->insert_custom(i + this->nxt[j]->jump, s, idx);
    }
    void insert_standard(const auto &i, const auto &s) {
        if (i == int(s.size()))
            return;
        int j = (s[i] - '0');
        if (this->nxt[j] == NULL)
            this->edges += 1,
            this->nxt[j] = new trie_node();
        this->nxt[j]->insert_standard(i + 1, s);
    }
    void sort_indexes() {
        sort(this->indexes.begin(), this->indexes.end());
        for (int i = 0; i < 2; ++i)
            if (this->nxt[i] != NULL)
                this->nxt[i]->sort_indexes();
    }
    int query(const auto &i, const auto &X, const auto &L, const auto &R) {
        if (i == int(X.size()))
            return *lower_bound(this->indexes.begin(), this->indexes.end(), L) + 1;
        for (int j = (i < 0) ? 1 : ((X[i] - '0') ^ 1); true; j ^= 1) {
            if (this->nxt[j] == NULL)
                continue;            
            int idx = lower_bound(this->nxt[j]->indexes.begin(), this->nxt[j]->indexes.end(), L) - this->nxt[j]->indexes.begin();
            if (idx != int(this->nxt[j]->indexes.size()) and this->nxt[j]->indexes[idx] <= R)
                return this->nxt[j]->query(i + this->nxt[j]->jump, X, L, R);
        }
    }
};

vector< vector<int> > build_sparse_table(const auto &N, const auto &input) {
    const int M = log2(N) + 5;
    vector< vector<int> > st(N);
    for (int i = 0; i < N; ++i)
        st[i] = vector<int>(M);
    for (int i = 0; i < N; ++i)
        st[i][0] = int(input[i].size());
    for (int j = 1; j < M; ++j)
        for (int i = 0; i + (1 << j) <= N; ++i)
            st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j-1]);
    return st;
}

int query_sparse_table(const auto &x, const auto &y, const auto &st) {
    int dist = y - x + 1;
    int z = 31 - __builtin_clz(dist);
    return max(st[x][z], st[x + dist - (1 << z)][z]);
}

string convert(const string &s) {
    for (int i = 0; i < int(s.size()); ++i)
        if (s[i] != '0')
            return s.substr(i, int(s.size()) - i);
    return "";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<trie_node*> trie(MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; ++i)
        trie[i] = new trie_node();
    vector<string> input;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        input.push_back(convert(s));
    }
    for (const auto &s: input)
        trie[int(s.size())]->insert_standard(0, s);
    for (int i = 0; i < MAX_SIZE; ++i)
        for (int j = 0; j < 2; ++j)
            if (trie[i]->nxt[j] != NULL)
                trie[i]->nxt[j]->build_radix_tree();
    for (int i = 0; i < N; ++i)
        trie[int(input[i].size())]->insert_custom(0, input[i], i);
    for (int i = 0; i < MAX_SIZE; ++i)
        trie[i]->sort_indexes();
    auto st = build_sparse_table(N, input);
    while (Q-- > 0) {
        int L, R; string X; cin >> L >> R >> X;
        L -= 1;
        R -= 1;
        X = convert(X);
        int size = query_sparse_table(L, R, st);
        if (size > int(X.size())) {
            cout << trie[size]->query(int(X.size()) - size, X, L, R) << '\n';
            continue;
        }
        int ans = -1;
        for (int i = 0; i < int(X.size()); ++i) {
            if (X[i] == '1')
                continue;
            size = int(X.size()) - i;
            int idx = lower_bound(trie[size]->indexes.begin(), trie[size]->indexes.end(), L) - trie[size]->indexes.begin();
            if (idx != int(trie[size]->indexes.size()) and trie[size]->indexes[idx] <= R) {
                ans = trie[size]->query(i, X, L, R);
                break;
            }
        }
        if (ans != -1) {
            cout << ans << '\n';
            continue;
        }
        for (int i = int(X.size()) - 1; i >= 0; --i) {
            size = int(X.size()) - i;
            int idx = lower_bound(trie[size]->indexes.begin(), trie[size]->indexes.end(), L) - trie[size]->indexes.begin();
            if (idx != int(trie[size]->indexes.size()) and trie[size]->indexes[idx] <= R) {
                ans = trie[size]->query(i, X, L, R);
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}