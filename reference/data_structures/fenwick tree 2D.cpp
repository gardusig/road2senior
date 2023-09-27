// ------------------ WARNING ----------------------------
// always index BIT in range [1, n]

#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;

int bit[N][N];

void update (const int x, const int y, const int val) {
    for (int i = x; i <= N; i += i & (-i))
        for (int j = y; j <= N; j += j & (-j))
            bit[i][j] += val;
}

int query (const int x, const int y) {
    int total = 0;
    for (int i = x; i > 0; i -= i & (-i))
        for (int j = y; j > 0; j -= j & (-j))
            total += bit[i][j];
    return total;
}

int solve (const int x0, const int y0, const int x1, const int y1) {
    int total = 0;
    total += query(x1, y1);
    total -= query(x1, y0 - 1);
    total -= query(x0 - 1, y1);
    total += query(x0 - 1, y0 - 1);
    return total;
}

int main () {
    memset(bit, 0, sizeof bit);
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x; scanf("%d", &x);
            update(i, j, x);
        }
    }
    while (m-- > 0) {
        int x0, y0, x1, y1; scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
        printf("%d\n", solve(x0, y0, x1, y1));
    }
    return 0;
}