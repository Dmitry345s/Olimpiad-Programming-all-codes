#include<bits/stdc++.h>

using namespace std;

int MAX = 105;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
vector<int> now_pair(MAX, -1);
int timer = 1;

bool try_kuhn(int v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1 || try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        string now;
        cin >> now;
        for (int j = 0; j < (int)s.size(); ++j) {
            for (int l = 0; l < 6; ++l) {
                if (s[j] == now[l]) {
                    g[j].push_back(i);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < (int)s.size(); ++i) {
        if (try_kuhn(i)) {
            timer++;
        }
    }
    if (timer - 1 != (int)s.size()) {
        cout << "NO" << endl;
        return 0;
    }
    vector<int> ans((int)s.size());
    for (int i = 0; i < n; ++i) {
        if (now_pair[i] != -1) {
            ans[now_pair[i]] = i;
        }
    }
    cout << "YES" << endl;
    for (int i = 0; i < (int)s.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
