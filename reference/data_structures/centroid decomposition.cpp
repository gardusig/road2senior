#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int size[N];
set<int> g[N], centroid_tree[N];

void build_size (const int i, const int p) {
    size[i] = 1;
    for (int j : g[i])
        if (j != p)
            build_size(j, i), 
            size[i] += size[j];
}

int find_centroid (const int i, const int p, const int total) {
    for (int j : g[i])
        if (j != p and (size[j] << 1) > total)
            return find_centroid(j, i, total);
    return i;
}

int build_centroid (int i, const int p) {
    build_size(i, p);
    i = find_centroid(i, p, size[i]);
    for (int k : g[i])
        if (k != p) {
            g[k].erase(i);
            int j = build_centroid(k, i);
            centroid_tree[i].insert(j);
            centroid_tree[j].insert(i);
        }
    g[i].clear();
    return i;
}

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y; scanf("%d %d", &x, &y);
        g[x].insert(y), g[y].insert(x);
    }
    int root = build_centroid(0, -1);
    return 0;
}