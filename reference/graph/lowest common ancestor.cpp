#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
const int N = 1e5 + 10, M = 25;
const int K = 5 * 1e3 + 10;
const int INF = 12345678;

int n, k, q;
vector<ii> g[N];
int value[K], cost[K], dp[K][K];
int lca[N][M], height[N], highest[N][M];

void build_lca (int i, int wt, int p) {
    lca[i][0] = p;
    highest[i][0] = wt;
    height[i] = height[p] + 1;
    for (int j = 1; j < M; ++j)
        lca[i][j] = lca[lca[i][j-1]][j-1],
        highest[i][j] = max(highest[i][j-1], highest[lca[i][j-1]][j-1]);
    for (int j = 0; j < g[i].size(); ++j)
        if (g[i][j].first != p)
            build_lca(g[i][j].first, g[i][j].second, i);
}

int query_lca (int x, int y) {
    if (height[x] < height[y])
        swap(x, y);
    int current = height[x] - height[y];
    for (int j = 0; j < M; ++j)
        if (current & (1 << j))
            x = lca[x][j];
    if (x == y)
        return x;
    for (int j = M-1; j >= 0; --j)
        if (lca[x][j] != lca[y][j])
            x = lca[x][j], y = lca[y][j];
    return lca[x][0];
}

int query_dist (int x, int y) {
    return height[x] + height[y] - (height[query_lca(x, y)] << 1) + 1;
}

int solve (int pos, int current) {
    if (current > k)
        return -INF;
    if (pos == q or current == k)
        return 0;
    if (dp[pos][current] != -1)
        return dp[pos][current];
    int ans = solve(pos+1, current);
    ans = max(ans, value[pos] + solve(pos+1, current + cost[pos]));
    return dp[pos][current] = ans;
}

int query_highest (int x, int y) {
    if (height[x] < height[y])
        swap(x, y);
    int ans = 0;
    int current = height[x] - height[y];
    for (int j = 0; j < M; ++j)
        if (current & (1 << j))
            ans = max(ans, highest[x][j]),
            x = lca[x][j];
    if (x == y)
        return ans;
    for (int j = M-1; j >= 0; --j)
        if (lca[x][j] != lca[y][j])
            ans = max(ans, max(highest[x][j], highest[y][j])),
            x = lca[x][j],
            y = lca[y][j];
    return max(ans, max(highest[x][0], highest[y][0]));
}

int main () {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i)
        g[i].clear();
    for (int i = 1; i < n; ++i) {
        int x, y, z; 
        scanf("%d %d %d", &x, &y, &z); --x, --y;
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    height[0] = 0;
    build_lca(0, 0, 0);
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int x, y; scanf("%d %d", &x, &y); --x, --y;
        value[i] = query_highest(x, y);
        cost[i] = query_dist(x, y);
    }
    for (int i = 0; i < q; ++i)
        for (int j = 0; j < k; ++j)
            dp[i][j] = -1;
    int ans = solve(0, 0);
    printf("%d\n", (!ans ? -1 : ans));
    return 0;
}