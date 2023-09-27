#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> dd;
const int N = 1e3 + 10;
const double INF = 1e18 + 10;

double dist[N];
vector< pair<int, dd> > g[N];

double solve (int n, double t) {
    for (int i = 0; i < n; ++i)
        dist[i] = INF;
    priority_queue< pair<double, int> > pq; 
    dist[0] = 0, pq.push(make_pair(-dist[0], 0));
    while (!pq.empty()) {
        int i = pq.top().second; pq.pop();
        if (i == n-1)
            return dist[i];
        for (auto j : g[i].size()) {
            double cost = dist[i] + (j.second.first * t) + j.second.second;
            if (cost < dist[j.first])
                dist[j.first] = cost, pq.push(make_pair(-cost, j.first));
        }
    }
    return -INF;
}

int main () {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y; double a, b; 
        scanf("%d %d %lf %lf", &x, &y, &a, &b); --x, --y;
        g[x].push_back(make_pair(y, make_pair(a, b)));
        g[y].push_back(make_pair(x, make_pair(a, b)));
    }
    double lo = 0, hi = 24 * 60;
    for (int i = 0; i < 80; ++i) {
        const double mid = (hi - lo) / 3.0;
        const double mid1 = lo + mid, mid2 = hi - mid;
        if (solve(n, mid1) > solve(n, mid2))
            hi = mid2;
        else
            lo = mid1;
    }
    printf("%.5lf\n", solve(n, lo));
    return 0;
}