#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int n;
int kmp[N];
string text, pattern;

void build_kmp () {
    kmp[0] = 0;
    for (int i = 1, j = 0; i < pattern.size(); ++i) {
        while (j and pattern[i] != pattern[j])
            j = kmp[j-1];
        if (pattern[i] == pattern[j])
            ++j;
        kmp[i] = j;
    }
}

int query () {
    int ans = 0;
    for (int i = 0, j = 0; i < text.size(); ++i) {
        while (j and text[i] != pattern[j])
            j = kmp[j-1];
        if (text[i] == pattern[j] and ++j == pattern.size())
            ++ans, j = kmp[j-1];
    }
    return ans;
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    getline(cin, text);
    getline(cin, pattern);
    build_kmp();
    cout << query() << '\n';
    return 0;
}