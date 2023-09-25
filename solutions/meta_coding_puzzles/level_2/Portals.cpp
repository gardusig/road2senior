#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

const std::vector<int> dx{0, 0, 1, -1};
const std::vector<int> dy{1, -1, 0, 0};

std::vector<std::pair<int, int>> getPositionsWithChar(
    const vector<vector<char>>& G, const char C) {
  std::vector<std::pair<int, int>> positionsWithChar;
  for (int i = 0; i < G.size(); i += 1) {
    for (int j = 0; j < G[i].size(); j += 1) {
      if (G[i][j] == C) {
        positionsWithChar.push_back({i, j});
      }
    }
  }
  return positionsWithChar;
}

bool isPositionValid(const int R, const int C, const vector<vector<char>> G,
                     const int row, const int column) {
  if (row < 0 or row >= R) {
    return false;
  }
  if (column < 0 or column >= C) {
    return false;
  }
  return G[row][column] != '#';
}

int bfs(const int R, const int C, const vector<vector<char>> G,
        const std::pair<int, int>& startPosition,
        const std::unordered_map<char, std::vector<std::pair<int, int>>>&
            portalsWithChar) {
  std::unordered_map<int, std::unordered_map<int, int>> dist;
  std::queue<std::pair<int, int>> q;
  q.push(startPosition);
  dist[startPosition.first][startPosition.second] = 0;
  while (!q.empty()) {
    const int i = q.front().first;
    const int j = q.front().second;
    q.pop();
    const char currentChar = G[i][j];
    const int currentDist = dist[i][j];
    if (currentChar == 'E') {
      return currentDist;
    }
    const int nxtDist = currentDist + 1;
    for (int k = 0; k < 4; k += 1) {
      const int x = i + dx[k];
      const int y = j + dy[k];
      if (!isPositionValid(R, C, G, x, y)) {
        continue;
      }
      if (dist.count(x) and dist[x].count(y) and nxtDist >= dist[x][y]) {
        continue;
      }
      dist[x][y] = nxtDist;
      q.push({x, y});
    }
    const auto it = portalsWithChar.find(currentChar);
    if (it != portalsWithChar.end()) {
      for (const auto& position : it->second) {
        const int x = position.first;
        const int y = position.second;
        if (dist.count(x) and dist[x].count(y) and nxtDist >= dist[x][y]) {
          continue;
        }
        dist[x][y] = nxtDist;
        q.push({x, y});
      }
    }
  }
  return -1;
}

int getSecondsRequired(int R, int C, vector<vector<char>> G) {
  std::pair<int, int> startPosition = getPositionsWithChar(G, 'S')[0];

  std::unordered_map<char, std::vector<std::pair<int, int>>> portalsWithChar;
  for (char c = 'a'; c <= 'z'; c += 1) {
    const auto portalWithChar = getPositionsWithChar(G, c);
    if (portalWithChar.empty()) {
      continue;
    }
    portalsWithChar[c] = portalWithChar;
  }

  return bfs(R, C, G, startPosition, portalsWithChar);
}
