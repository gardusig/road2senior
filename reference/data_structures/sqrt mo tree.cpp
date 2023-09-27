#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> lii;
const int N = 4e5 + 5;
const int M = log2(N) + 5;
const int O = 1e5 + 5;

int n, m;
char used[N];
int current, gifts;
vector<int> g[N], mo;
unordered_map<int, int> Hash;
vector< pair<ii, ii> > query;
int lca[N][M], depth[N], value[N], in[N], out[N], v[N << 1], block[N << 1], f[N], ans[O];

int convert (const int x) {
    if (!Hash.count(x))
        Hash[x] = Hash.size();
    return Hash[x];
}

void dfs (const int i, const int p) {
    lca[i][0] = p;
    depth[i] = depth[p] + 1;
    for (int j = 1; j < M; ++j)
        lca[i][j] = lca[lca[i][j-1]][j-1];
    v[current] = i, in[i] = current++;
    for (int j = 0; j < g[i].size(); ++j)
        if (g[i][j] != p)
            dfs(g[i][j], i);
    v[current] = i, out[i] = current++;
}

int query_lca (int x, int y) {
    if (depth[x] < depth[y])
        swap(x, y);
    int dist = depth[x] - depth[y];
    for (int i = 0; i < M; ++i)
        if (dist & (1 << i))
            x = lca[x][i];
    if (x == y)
        return x;
    for (int i = M - 1; i >= 0; --i)
        if (lca[x][i] != lca[y][i])
            x = lca[x][i], y = lca[y][i];
    return lca[x][0];
}

void walk (const int l, const int r) {
    for (int i = l; i <= r; ++i) {
        if (used[v[i]] and --f[value[v[i]]] == 0)
            --gifts;
        else if (!used[v[i]] and ++f[value[v[i]]] == 1)
            ++gifts;
        used[v[i]] ^= 1;
    }
}

bool compare (const pair<ii, ii> a, const pair<ii, ii> b) {
    if (block[a.first.first] == block[b.first.first])
        return a.first.second < b.first.second;
    return a.first.first < b.first.first;
}

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        used[i] = 0;
        int x; scanf("%d", &x);
        value[i] = convert(x);
    }
    for (int i = 1; i < n; ++i) {
        int x, y; scanf("%d %d", &x, &y); --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    current = 0, depth[0] = -1, dfs(0, 0);
    for (int i = 0; i < m; ++i) {
        int x, y; scanf("%d %d", &x, &y); --x, --y;
        if (in[x] > in[y])
            swap(x, y);
        int z = query_lca(x, y);
        if (x == z)
            query.push_back(make_pair(make_pair(in[x], in[y]), make_pair(-1, i)));
        else
            query.push_back(make_pair(make_pair(out[x], in[y]), make_pair(in[z], i)));
    }
    int block_size = sqrt(current) + 1;
    for (int i = 0; i < current; ++i)
        block[i] = (i / block_size);
    sort(query.begin(), query.end(), compare);
    gifts = 0, walk(0, 0);
    for (int i = 0, l = 0, r = 0; i < m; ++i) {
        int x = query[i].first.first;
        int y = query[i].first.second;
        int z = query[i].second.first;
        walk(min(l, x), max(l, x) - 1);
        walk(min(r, y) + 1, max(r, y));
        if (z != -1)
            walk(z, z);
        ans[query[i].second.second] = gifts, l = x, r = y;
        if (z != -1)
            walk(z, z);
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}