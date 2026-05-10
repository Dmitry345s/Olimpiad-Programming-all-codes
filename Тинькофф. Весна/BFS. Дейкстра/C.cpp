#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    int x, y;
    cin >> x >> y;
    int x1, y1;
    cin >> x1 >> y1;
    vector<pair<int, int>> m(8);
    m[0] = {2, 1};
    m[1] = {2, -1};
    m[2] = {-2, 1};
    m[3] = {-2, -1};
    m[4] = {1, 2};
    m[5] = {1, -2};
    m[6] = {-1, 2};
    m[7] = {-1, -2};
    vector<vector<int>> g(n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < 8; ++l) {
                if (i + m[l].first >= 0 && i + m[l].first < n && j + m[l].second >= 0 && j + m[l].second < n) {
                    g[i * n + j].push_back((i + m[l].first) * n + j + m[l].second);
                }
            }
        }
    }
    int start = (x - 1) * n + y - 1, last = (x1 - 1) * n + y1 - 1;
    queue<int> q;
    q.push(start);
    vector<int> d(n * n, -1), p(n * n);
    vector<bool> used(n * n, false);
    d[start] = 0;
    p[start] = -1;
    used[start] = true;
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
    cout << d[last] << endl;
    int v = last;
    vector<int> ans;
    ans.push_back(v);
    while (p[v] != -1) {
        ans.push_back(p[v]);
        v = p[v];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] / n + 1 << " " << ans[i] % n + 1 << endl;
    }
}
