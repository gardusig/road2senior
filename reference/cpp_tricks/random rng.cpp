#include <bits/stdc++.h>

std::mt19937 rng(
    int(std::chrono::steady_clock::now().time_since_epoch().count()));

void shuffle(std::vector<int> &v) { std::shuffle(v.begin(), v.end(), rng); }
