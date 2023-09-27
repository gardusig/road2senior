#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
const int INF = 1e9 + 10;

int n, m;
int dist[N][N];

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = INF;
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;
    while (m-- > 0) {
        int x, y, z; scanf("%d %d %d", &x, &y, &z); --x, --y;
        dist[x][y] = min(dist[x][y], z);
        dist[y][x] = min(dist[y][x], z);
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return 0;
}