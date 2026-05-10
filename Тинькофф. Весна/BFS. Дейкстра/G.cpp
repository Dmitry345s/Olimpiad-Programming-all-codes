#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int mod(string x, int k) {
    string k2 = to_string(k);
    while (x.size() > k2.size() || stoi(x) > stoi(k2)) {
        string t = x.substr(0, k2.size());
        if (stoi(t) < stoi(k2)) {
            t = x.substr(0, k2.size() + 1);
            x = to_string(stoi(t) % stoi(k2)) + x.substr(k2.size() + 1, x.size() - k2.size());
        } else {
            x = to_string(stoi(t) % stoi(k2)) + x.substr(k2.size(), x.size() - k2.size() + 1);
        }
    }
    int ans = stoi(x);
    return ans;
}
int main() {
    string x;
    int k;
    cin >> x >> k;
    int b;
    cin >> b;
    vector<int> D(b);
    for (int i = 0; i < b; ++i) {
        cin >> D[i];
    }
    vector<vector<pair<int, int>>> g(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < D.size(); ++j) {
            g[(i * 10 + D[j]) % k].push_back({i, D[j]});
        }
    }
    int start = mod(x, k);
    vector<int> d(k, 100000);
    vector<pair<int, int>> p(k);
    vector<bool> used(k, false);
    queue<int> q;
    used[0] = true;
    q.push(0);
    d[0] = 0;
    p[0].first = -1;
    p[0].second = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].first, from = g[v][i].second;
            if (!used[to]) {
                d[to] = d[v] + 1;
                p[to].first = from;
                p[to].second = v;
                used[to] = true;
                q.push(to);
            } else {
                if (d[to] == d[v] + 1) {
                    if (p[to].first >= from) {
                        p[to].first = from;
                        p[to].second = v;
                    }
                }
            }
        }
    }
    if (d[start] == 100000) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> ans;
    int v = start;
    while (p[v].second != -1) {
        ans.push_back(p[v].first);
        v = p[v].second;
    }
    cout << x;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i];
    }
}
