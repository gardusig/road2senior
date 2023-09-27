#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
const int N = 3 * 1e5 + 10;
const int INF = 1e9 + 10;
const ll MOD = 1000000007;

ll n, m;
ll cost[N];
char used[N];
stack<int> aux;
ii current, ans;
vector<int> g[N], t[N];

void dfs_g (ll i) {
    used[i] = true;
    for (ll j = 0; j < g[i].size(); ++j)
        if (!used[g[i][j]])
            dfs_g(g[i][j]);
    aux.push(i);
}

void dfs_t (ll i) {
    if (cost[i] < current.first)
        current = make_pair(cost[i], 1);
    else if (cost[i] == current.first)
        ++current.second;
    used[i] = true;
    for (ll j = 0; j < t[i].size(); ++j)
        if (!used[t[i][j]])
            dfs_t(t[i][j]);
}

void build () {
    for (ll i = 0; i < n; ++i)
        used[i] = false;
    for (ll i = 0; i < n; ++i)
        if (!used[i])
            dfs_g(i);
    ans = make_pair(0, 1);
    for (ll i = 0; i < n; ++i)
        used[i] = false;
    while (!aux.empty()) {
        if (!used[aux.top()]) {
            current = make_pair(INF, INF);
            dfs_t(aux.top());
            ans.first += current.first;
            ans.second *= current.second;
            ans.second %= MOD;
        }
        aux.pop();
    }
}

int main () {
    scanf("%lld", &n);
    for (ll i = 0; i < n; ++i)
        scanf("%lld", &cost[i]);
    scanf("%lld", &m);
    for (ll i = 0; i < m; ++i) {
        ll x, y; scanf("%lld %lld", &x, &y); --x, --y;
        g[x].push_back(y);
        t[y].push_back(x);
    }
    build();
    printf("%lld %lld\n", ans.first, ans.second);
    return 0;
}