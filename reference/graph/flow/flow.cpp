#include <bits/stdc++.h>
using namespace std;

class edge {
private:
  edge(const auto &to, const auto &flow, const auto &capacity) {
    this->to = to;
    this->flow = flow;
    this->capacity = capacity;
  }
public:
  int to, flow, capacity;
  static void add(const auto &x, const auto &y, const auto &capacity, auto &g, auto &edges) {
    g[x].push_back(int(edges.size()));
    edges.push_back(edge(y, 0, capacity));
    g[y].push_back(int(edges.size()));
    edges.push_back(edge(x, 0, 0));
  }
};

class ford_fulkerson {
private:
    ford_fulkerson() {}
    static int dfs(const int& i, const int& flow, const int& sink, const vector< vector<int> >& g, vector<edge>& edges, vector<int>& seen, int& current) {
        if (i == sink)
            return flow;
        seen[i] = current;
        for (const int& j : g[i])
            if (seen[edges[j].to] < current and edges[j].flow < edges[j].capacity)
                if (int nxt = dfs(edges[j].to, min(flow, edges[j].capacity - edges[j].flow), sink, g, edges, seen, current)) {
                    edges[j].flow += nxt, edges[j ^ 1].flow -= nxt;
                    return nxt;
                }
        return 0;
    }
public:
    static int solve(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges) {
        vector<int> seen(N, 0);
        int ans = 0, current = 0;
        while (int i = dfs(source, INT_MAX, sink, g, edges, seen, ++current))
            ans += i;
        return ans;
    }
};

class edmonds_karp {
private:
    edmonds_karp() {}
    static int bfs(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges, vector<int>& seen, vector<int>& parent, int& current) {
        queue< pair<int, int> > q;
        seen[source] = current;
        q.push({source, -1});
        while (!q.empty()) {
            int i = q.front().first;
            int last_edge = q.front().second;
            q.pop();
            if (i == sink) {
                int flow = INT_MAX;
                for (int j = last_edge; j != -1; j = parent[j])
                    flow = min(flow, edges[j].capacity - edges[j].flow);
                for (int j = last_edge; j != -1; j = parent[j])
                    edges[j].flow += flow, edges[j ^ 1].flow -= flow;
                return flow;
            }
            for (const int& j : g[i])
                if (seen[edges[j].to] < current and edges[j].flow < edges[j].capacity)
                    parent[j] = last_edge,
                    seen[edges[j].to] = current,
                    q.push({edges[j].to, j});
        }
        return 0;
    }
public:
    static int solve(const int& source, const int& sink, const vector< vector<int> >& g, vector<edge>& edges) {
        vector<int> seen(N, 0);
        vector<int> parent(N, 0);
        int ans = 0, current = 0;
        while (int i = bfs(source, sink, g, edges, seen, parent, ++current))
            ans += i;
        return ans;
    }
};

class dinic {
private:
  dinic() {}
  static int bfs(const auto &source, const auto &sink, const auto &g, const auto &edges, auto &level, const auto &vertexes) {
    fill(level.begin(), level.end(), INT_MAX);
    queue< int > q;
    level[source] = 0;
    q.push(source);
    while (q.empty() == false) {
      int i = q.front(); 
      q.pop();
      for (const auto &j : g[i]) {
        if (level[edges[j].to] > level[i] + 1 and edges[j].flow < edges[j].capacity) {
          level[edges[j].to] = level[i] + 1;
          q.push(edges[j].to);
        }
      }
    }
    return level[sink] < INT_MAX;
  }
  static int dfs(const auto &i, const auto &sink, const auto &flow, const auto &g, auto &edges, const auto &level, auto &start) {
    if (i == sink) {
      return flow;
    }
    while (start[i] < int(g[i].size())) {
      int j = g[i][start[i]++];
      if (level[edges[j].to] == level[i] + 1 and edges[j].flow < edges[j].capacity) {
        if (int nxt = dfs(edges[j].to, sink, min(flow, edges[j].capacity - edges[j].flow), g, edges, level, start) > 0) {
          edges[j].flow += nxt;
          edges[j ^ 1].flow -= nxt;
          return nxt;
        }
      }
    }
    return 0;
  }
public:
  static int solve(const auto &source, const auto &sink, const auto &g, auto &edges, const auto &vertexes) {
    int ans = 0;
    vector< int > level(vertexes), start(vertexes);
    while (bfs(source, sink, g, edges, level, vertexes) == true) {
      fill(start.begin(), start.end(), 0);
      while (int current_flow = dfs(source, sink, INT_MAX, g, edges, level, start) > 0) {
        ans += current_flow;
      }
    }
    return ans;
  }
};

bool valid(const auto &a, const auto &b, const auto &s) {
    long long kappa = 1LL * (a.first - b.first) * (a.first - b.first);
    long long keepo = 1LL * (a.second - b.second) * (a.second - b.second);
    return sqrt(kappa + keepo) < s;
}

int main() {
    int n, m, s; cin >> n >> m >> s; s -= 10;
    vector< pair< int, int > > beagles(n);
    for (int i = 0; i < n; ++i)
        cin >> beagles[i].first >> beagles[i].second;
    vector< pair< pair< int, int>, int > > bowls(m);
    for (int i = 0; i < m; ++i)
        cin >> bowls[i].first.first >> bowls[i].first.second >> bowls[i].second;
    int source = 0, sink = 1;
    int vertexes = n + m + 2;
    vector<edge> edges;
    vector< vector< int > > g(vertexes);
    for (int i = 0; i < n; ++i)
        edge::add(source, 2 + i, 1, g, edges);
    for (int j = 0; j < m; ++j)
        edge::add(2 + n + j, sink, bowls[j].second, g, edges);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (valid(beagles[i], bowls[j].first, s) == true)
                edge::add(2 + i, 2 + n + j, 1, g, edges);
    return cout << (dinic::solve(source, sink, g, edges, vertexes) == n ? "YES" : "NO") << '\n', 0;
}