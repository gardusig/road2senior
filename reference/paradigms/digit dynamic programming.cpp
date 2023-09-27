#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 60;

int v[N];
ll dp[N][N][2];

void build (const ll x) {
    for (int i = 0; i < N; ++i)
        v[N - i - 1] = (x & (1LL << i)) ? 1 : 0;
    memset(dp, -1, sizeof dp);
}

ll solve (const int i, const int j, const bool less) {
    if (i == N)
        return j;
    if (dp[i][j][less] != -1)
        return dp[i][j][less];
    ll ans = 0;
    int limit = (less) ? 1 : v[i];
    for (int k = 0; k <= limit; ++k)
        ans += solve(i + 1, j + k, less | k < limit);
    return dp[i][j][less] = ans;
}

int main () {
    ll x, y;
    while (scanf("%lld %lld", &x, &y) == 2) {
        ll ans = 0;
        build(y);
        ans += solve(0, 0, 0);
        build(x - 1);
        ans -= solve(0, 0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}