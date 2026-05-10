#include<bits/stdc++.h>
#include "trick.h"

using namespace std;

//vector<vector<int>> shuffle(vector<vector<int>> q) {return vector<vector<int>>{{1}};}

vector<int> trick(int n, int b, int k) {
    vector<vector<int>> g1;
    vector<vector<int>> g2;
    vector<vector<int>> g3;
    vector<vector<int>> g4;
    for (int i = 1; i <= n; i += 2) {
        g1.push_back({i, i + 1});
    }
    for (int i = 2; i < n; i += 2) {
        g2.push_back({i, i + 1});
    }
    g2.push_back({1, n});
    g3.push_back({1, 2});
    if (n % 4 == 2) {
        for (int i = 3; i <= n; i += 4) {
            g3.push_back({i, i + 2});
            g3.push_back({i + 1, i + 3});
        }
    } else {
        g3.push_back({n, n - 5});
        g3.push_back({n - 4, n - 2});
        g3.push_back({n - 3, n - 1});
        for (int i = 3; i < n - 5; i += 4) {
            g3.push_back({i, i + 2});
            g3.push_back({i + 1, i + 3});
        }
    }
    g4.push_back({1, n});
    if (n % 4 == 2) {
        for (int i = 2; i < n; i += 4) {
            g4.push_back({i, i + 2});
            g4.push_back({i + 1, i + 3});
        }
    } else {
        g4.push_back({2, 7});
        g4.push_back({3, 5});
        g4.push_back({4, 6});
        for (int i = 8; i < n; i += 4) {
            g4.push_back({i, i + 2});
            g4.push_back({i + 1, i + 3});
        }
    }
    vector<vector<int>> a1 = shuffle(g1);
    vector<vector<int>> a2 = shuffle(g2);
    vector<vector<int>> a3 = shuffle(g3);
    vector<vector<int>> a4 = shuffle(g4);
    vector<vector<int>> g(n + 1);
    for (auto val : a1) {
        int u = val[0];
        int v = val[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (auto val : a2) {
        int u = val[0];
        int v = val[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (auto & val : a1) sort(val.begin(), val.end());
    for (auto & val : a2) sort(val.begin(), val.end());
    for (auto & val : a3) sort(val.begin(), val.end());
    for (auto & val : a4) sort(val.begin(), val.end());
    vector<int> mb1;
    vector<int> mb2;
    for (auto val : a3) {
        for (auto val2 : a1) {
            if (val == val2) {
                mb1 = val;
            }
        }
    }
    for (auto val : a4) {
        for (auto val2 : a2) {
            if (val == val2) {
                mb2 = val;
            }
        }
    }
    int in1, in2;
    if (mb1[0] == mb2[0] || mb1[0] == mb2[1]) {
        in1 = mb1[0];
        in2 = mb1[1];
    } else {
        in1 = mb1[1];
        in2 = mb1[0];
    }
    vector<int> us(n + 1);
    vector<int> ans;
    ans.push_back(in1);
    us[in1] = 1;
    int now = in2;
    for (int i = 0; i < n - 1; ++i) {
        ans.push_back(now);
        us[now] = 1;
        for (int to : g[now]) {
            if (us[to]) continue;
            now = to;
        }
    }
    return ans;
}
