#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int N = 21;

int n, m;
ll kappa;
ll v[N][N];
map<ll, ll> dp[2][N][N];

int main () {
    scanf("%d %d %lld", &n, &m, &kappa);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%lld", &v[i][j]);
    int middle = (n + m - 1) >> 1;
    dp[0][0][0][v[0][0]] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (i + j <= middle) {
                for (auto k : dp[0][i][j]) {
                    if (i + 1 < n)
                        dp[0][i + 1][j][k.first ^ v[i + 1][j]] += k.second;
                    if (j + 1 < m)
                        dp[0][i][j + 1][k.first ^ v[i][j + 1]] += k.second;
                }
            }
    dp[1][n-1][m-1][v[n-1][m-1]] = 1;
    for (int i = n-1; i >= 0; --i)
        for (int j = m-1; j >= 0; --j)
            if (n - 1 + m - 1 - i - j <= middle) {
                for (auto k : dp[1][i][j]) {
                    if (i - 1 >= 0)
                        dp[1][i - 1][j][k.first ^ v[i - 1][j]] += k.second;
                    if (j - 1 >= 0)
                        dp[1][i][j - 1][k.first ^ v[i][j - 1]] += k.second;
                }
            }
    ll ans = 0;
    for (int i = n-1, j = middle - i; i >= 0; --i, ++j)
        for (auto k : dp[0][i][j])
            ans += (k.second * dp[1][i][j][k.first ^ kappa ^ v[i][j]]);
    return printf("%lld\n", ans), 0;
}