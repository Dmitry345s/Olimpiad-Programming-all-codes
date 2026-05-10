#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int main() {
    vector<vector<int>> g(10000);
    for (int i = 1000; i < 10000; ++i) {
        if (i % 10 != 1) {
            g[i].push_back(i - 1);
        }
        if (i / 1000 != 9) {
            g[i].push_back(i + 1000);
        }
        g[i].push_back(i % 1000 * 10 + i / 1000);
        g[i].push_back(i % 10 * 1000 + i / 10);
    }
    int s, e;
    cin >> s >> e;
    vector<int> d(10000, 1000000), p(10000);
    vector<bool> used(10000, false);
    queue<int> q;
    d[s] = 0;
    p[s] = -1;
    q.push(s);
    used[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!used[to]) {
                d[to] = d[v] + 1;
                p[to] = v;
                q.push(to);
                used[to] = true;
            }
        }
    }
    vector<int> ans;
    ans.push_back(e);
    int v = e;
    while (p[v] != -1) {
        ans.push_back(p[v]);
        v = p[v];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }
}
