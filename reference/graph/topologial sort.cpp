#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 112345;

stack< int > st;
bool used[MAX_SIZE];
vector< int > g[MAX_SIZE];

void dfs(const int &i) {
    used[i] = true;
    for (const int &j: g[i]) {
        if (used[j] == true) {
            continue;
        }
        dfs(j);
    }
    st.push(i);
}

void bfs_kahn() {
    vector< int > degree(MAX_SIZE, 0);
    for (int i = 0; i < N; i += 1) {
        for (const int &j: g[i]) {
            degree[j] += 1;
        }
    }
    queue< int > q;
    for (int i = 0; i < N; i += 1) {
        if (degree[i] == 0) {
            q.push(i);
            degree[i] = -1;
        }
    }
    while (q.empty() == false) {
        int i = q.front();
        q.pop();
        for (const int &j: g[i]) {
            degree[j] -= 1;
            if (degree[j] == 0) {
                q.push(j);
            }
        }
    }
}