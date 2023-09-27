#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, M = 1e5 + 10;

int n, w;
int val[N], wt[M], dp[2][M];

bool solve () {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= w; ++j) {
            if (!i or !j)
                dp[i & 1][j] = 0;
            else if (wt[i-1] <= j)
                dp[i & 1][j] = max(dp[(i-1) & 1][j], val[i-1] + dp[(i-1) & 1][j - wt[i-1]]);
            else
                dp[i & 1][j] = dp[(i-1) & 1][j];
        }
    }
    return (dp[n & 1][w] == w);
}

int main () {
    while (scanf("%d %d", &w, &n) != EOF) {
        if (!w and !n)
            break;
        for (int i = 0; i < n; ++i)
            scanf("%d", &val[i]), wt[i] = val[i];
        puts(solve() ? "sim" : "nao");
    }
    return 0;
}