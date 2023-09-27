#include <bits/stdc++.h>
using namespace std;

class dinic;
class dinossaur;
class edge;

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

class dinossaur {
public:
  int x, y, start, finish;
  dinossaur(const auto &x, const auto &y, const auto &start, const auto &finish) {
    this->x = x;
    this->y = y;
    this->start = start;
    this->finish = finish;
  }
  bool valid(const auto &other) {
    long long int dist = 0;
    dist += 1LL * (this->x - other.x) * (this->x - other.x);
    dist += 1LL * (this->y - other.y) * (this->y - other.y);
    return (sqrt(dist) + this->finish > other.start) ? false : true;
  }
  bool operator < (const auto &other) {
    if (this->start != other.start) {
      return this->start < other.start;
    }
    return this->finish < other.finish;
  }
};

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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int have, n;
  cin >> have >> n;
  vector< dinossaur > dinossaurs;
  for (int i = 0; i < n; i += 1) {
    int x, y, start, finish;
    cin >> x >> y >> start >> finish;
    dinossaurs.push_back(dinossaur(x, y, start, finish));
  }
  sort(dinossaurs.begin(), dinossaurs.end());
  vector< edge > edges;
  vector< vector< int > > g(n + n + 5);
  int source = 0, sink = 1;
  for (int i = 0; i < n; i += 1) {
    edge::add(source, i + 2, 1, g, edges);
    edge::add(i + 2 + n, sink, 1, g, edges);
  }
  for (int i = 0; i < n; i += 1) {
    for (int j = i + 1; j < n; j += 1) {
      if (dinossaurs[i].valid(dinossaurs[j])) {
        edge::add(i + 2, j + 2 + n, 1, g, edges);
      }
    }
  }
  int ans = n - dinic::solve(source, sink, g, edges, n + n + 2);
  cout << (ans > have ? "N" : "S") << '\n';
  return 0;
}