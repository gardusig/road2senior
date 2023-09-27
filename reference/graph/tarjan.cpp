#include <bits/stdc++.h>
using namespace std;

const int N = 112345;

class edge {
public:
    int to, id;
    edge (const int &to, const int &id) {
        this->to = to, this->id = id;
    }
};

vector<edge> g[N];
int current_time, n, m, components;
int size[N], component[N], pre[N], low[N];
char used[N], bridge[N], articulation_point[N];

void dfs_tarjan(const int &i, const int &p) {
    used[i] = true;
    pre[i] = low[i] = current_time++;
    for (auto &j : g[i]) {
        int children = 0;
        if (!used[j.to]) {
            dfs_tarjan(j.to, i);
            low[i] = min(low[i], low[j.to]);
            if (low[j.to] == pre[j.to])
                bridge[j.id] = true;
            if (i == p and ++children > 1)
                articulation_point[i] = true;
            if (i != p and low[j.to] >= pre[i])
                articulation_point[i] = true;
        }
        else if (j.to != p)
            low[i] = min(low[i], pre[j.to]);
    }
}

void build_tarjan() {
    current_time = 0;
    for (int i = 0; i < n; ++i)
        used[i] = articulation_point[i] = false;
    for (int i = 0; i < m; ++i)
        bridge[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs_tarjan(i, i);
}

void dfs_component(const int &i) {
    used[i] = true;
    ++size[component[i]];
    for (auto &j : g[i])
        if (!used[j.to])
            component[j.to] = bridge[j.id] ? component[i] : components++,
            dfs_component(j.to);
}

void build_components() {
    components = 0;
    for (int i = 0; i < n; ++i)
        size[i] = 0,
        used[i] = false,
        component[i] = i;
    for (int i = 0; i < n; ++i)
        if (!used[i])
            component[i] = components++,
            dfs_component(i);
}

int main() {
    int t; scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i)
            g[i].clear();
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d %d", &x, &y); --x, --y;
            g[x].push_back(edge(y, i));
            g[y].push_back(edge(x, i));
        }
        build_tarjan();
        build_components();
    }
    return 0;
}