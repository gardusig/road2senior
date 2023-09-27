#include <bits/stdc++.h>
using namespace std;

const int N = 1123;

int n, m;
int dp[N][N];
char s[N], have[N][N];

void build () {
    for (int j = 0; j < m; ++j) {
        stack<int> st;
        for (int i = 0; i <= n; ++i) {
            int current = (i < n) ? dp[i][j] : INT_MIN;
            while (!st.empty() and current < dp[st.top()][j]) {
                int top = st.top(); st.pop();
                int x = dp[top][j];
                int y = (st.empty()) ? i : (i - st.top() - 1);
                have[x][y] = have[y][x] = true;
            }
            st.push(i);
        }
    }
    for (int i = n; i > 0; --i)
        for (int j = m; j > 0; --j)
            if (have[i][j])
                have[i][j-1] = have[i-1][j] = true;
}

int main () {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = m - 1; j >= 0; --j)
            if (s[j] == '.')
                dp[i][j] = dp[i][j + 1] + 1;
    }
    build();
    int k; scanf("%d", &k);
    int area = 0, kappa = 0, keepo = 0;
    while (k-- > 0) {
        int x, y; scanf("%d %d", &x, &y);
        if (!have[x][y])
            continue;
        int current_area = x * y;
        if (current_area > area)
            area = current_area, kappa = x, keepo = y;
        else if (current_area == area and y > keepo)
            kappa = x, keepo = y;
    }
    return printf("%d %d\n", kappa, keepo), 0;
}