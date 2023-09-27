#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int parent[N], size[N];

void UNION (int x, int y) {
    if (size[x] > size[y])
        swap(x, y);
    size[x] += size[y];
    parent[y] = parent[x];
}

int FIND (const int x) {
    if (x != parent[x])
        parent[x] = FIND(parent[x]);
    return parent[x];
}

int main () {
    int n, q; scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
        parent[i] = i, size[i] = 1;
    while (q-- > 0) {
        int type, x, y; scanf("%d %d %d", &type, &x, &y);
        x = FIND(x), y = FIND(y);
        if (type == 1)
            puts(x == y ? "Yes" : "No");
        else
            UNION(x, y);
    }
    return 0;
}