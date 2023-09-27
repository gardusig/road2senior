#include <bits/stdc++.h>
using namespace std;
const int N = (100 + 5) << 1;
const int M = N * (N + 5);

class member {
public:
    double x, y, s;
    member (const int _x, const int _y, const double _s) :
        x(_x), y(_y), s(_s) {}
    double dist (const member other) {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)) / s;
    }
};

class edge {
public:
    double cost;
    int to, flow, cap, idx;
    edge (const int _to, const int _flow, const int _cap, const double _cost) :
        to(_to), flow(_flow), cap(_cap), cost(_cost) {}
};

double dist[N];
vector<int> g[N];
vector<edge> edges;
vector<member> members;
int seen[N], parent[M];
int n, m, source, sink, current;

void add_edge (const int x, const int y, const int cap, const double cost) {
    g[x].push_back(edges.size()), edges.push_back(edge(y, 0, cap, cost));
    g[y].push_back(edges.size()), edges.push_back(edge(x, 0, 0, -cost));
}

pair<int, double> dijkstra () {
    priority_queue< pair< pair<double, int>, pair<int, int> > > pq;
    dist[source] = 0.0, seen[source] = ++current, pq.push(make_pair(make_pair(-dist[source], INT_MAX), make_pair(-1, source)));
    while (pq.size()) {
        int i = pq.top().second.second;
        int flow = pq.top().first.second;
        int last_edge = pq.top().second.first;
        double current_cost = -pq.top().first.first;
        pq.pop();
        if (i == sink) {
            double cost = 0.0;
            for (; last_edge != -1; last_edge = parent[last_edge])
                cost += edges[last_edge].cost, edges[last_edge].flow += flow, edges[last_edge ^ 1].flow -= flow;
            return make_pair(flow, cost);
        }
        if (dist[i] < current_cost)
            continue;
        for (int j : g[i])
            if ((seen[edges[j].to] < current or dist[i] + edges[j].cost < dist[edges[j].to]) and edges[j].flow < edges[j].cap)
                parent[j] = last_edge,
                seen[edges[j].to] = current,
                dist[edges[j].to] = dist[i] + edges[j].cost,
                pq.push(make_pair(make_pair(-dist[edges[j].to], min(flow, edges[j].cap - edges[j].flow)), make_pair(j, edges[j].to)));
    }
    return make_pair(0, 0.0);
}

double solve () {
    double ans = 0.0;
    for (pair<int, double> nxt = dijkstra(); nxt.first > 0; nxt = dijkstra())
        ans += (nxt.second * nxt.first);
    return ans;
}

int main () {
    while (scanf("%d %d", &n, &m) == 2) {
        if (!n and !m)
            break;
        source = 0, sink = n + m + 1;
        edges.clear(), members.clear();
        for (int i = source; i <= sink; ++i)
            g[i].clear();
        for (int i = 1; i <= n; ++i) {
            int x, y; double s; scanf("%d %d %lf", &x, &y, &s);
            members.push_back(member(x, y, s));
            add_edge(source, i, 1, 0.0);
        }
        for (int i = 1; i <= m; ++i) {
            int x, y; scanf("%d %d", &x, &y);
            int accept; member checkpoint(x, y, 0.0);
            while (scanf("%d", &accept) == 1 and accept)
                add_edge(accept, n + i, 1, members[accept - 1].dist(checkpoint));
            add_edge(n + i, sink, 1, 0.0);
        }
        printf("%.1lf\n", solve());
    }
    return 0;
}