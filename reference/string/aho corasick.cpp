#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 7;
const int M = 26;

int n;
string s;
int ans[N];
stack<int> st;
int idx, total;
vector<int> g[N];
vector<string> v;

struct node {
    int id;
    node *link;
    node *nxt[M];
    set<int> end;

    node () {
        end.clear();
        link = NULL;
        id = total++;
        for (int i = 0; i < M; ++i)
            nxt[i] = NULL;
    }

    void add (const int &i) {
        if (i == s.length()) {
            end.insert(idx);
            return;
        }
        if (!nxt[s[i] - 'a'])
            nxt[s[i] - 'a'] = new node();
        nxt[s[i] - 'a']->add(i + 1);
    }

    void build () {
        queue<node*> q;
        for (int i = 0; i < M; ++i) {
            if (nxt[i]) {
                nxt[i]->link = this;
                nxt[i]->end.insert(end.begin(), end.end());
                q.push(nxt[i]);
            }
            else
                nxt[i] = this;
        }
        while (q.size()) {
            node *current = q.front(); q.pop();
            for (int i = 0; i < M; ++i) {
                if (current->nxt[i]) {
                    node *fail = current->link;
                    while (!fail->nxt[i])
                        fail = fail->link;
                    fail = fail->nxt[i];
                    current->nxt[i]->link = fail;
                    current->nxt[i]->end.insert(fail->end.begin(), fail->end.end());
                    q.push(current->nxt[i]);
                }
            }
        }
    }

    void search (const int &i) {
        for (set<int>::iterator j = end.begin(); j != end.end(); ++j)
            if (idx != *j)
                g[idx].push_back(*j);
        if (i == s.size())
            return;
        int j = s[i] - 'a';
        node *current = this;
        while (!current->nxt[j] and current != current->link)
            current = current->nxt[j];
        current->nxt[j]->search(i + 1);
    }

    void clear () {
        for (int i = 0; i < M; ++i)
            if (nxt[i] and nxt[i]->id > id)
                nxt[i]->clear();
        delete this;
    }
};

void dfs (const int &i) {
    ans[i] = 1;
    for (int j = 0; j < g[i].size(); ++j)
        if (!ans[g[i][j]])
            dfs(g[i][j]);
    st.push(i);
}

int solve () {
    for (int i = 0; i < n; ++i)
        if (!ans[i])
            dfs(i);
    for (; st.size(); st.pop()) {
        int i = st.top();
        for (int j = 0; j < g[i].size(); ++j)
            ans[g[i][j]] = max(ans[g[i][j]], ans[i] + 1);
    }
    int best = 0;
    for (int i = 0; i < n; ++i)
        best = max(best, ans[i]);
    return best;
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        if (!n)
            break;
        total = 0;
        v.clear();
        node *root = new node();
        for (int i = 0; i < n; ++i)
            ans[i] = 0, g[i].clear();
        getline(cin, s);
        for (int i = 0; i < n; ++i) {
            idx = i;
            getline(cin, s);
            root->add(0);
            v.push_back(s);
        }
        root->build();
        for (int i = 0; i < v.size(); ++i) {
            idx = i;
            s = v[i];
            root->search(0);
        }
        cout << solve() << '\n';
        root->clear();
    }
    return 0;
}