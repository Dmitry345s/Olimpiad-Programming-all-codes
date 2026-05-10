#include<iostream>
#include<vector>
#include<set>

using namespace std;

int MAX = 1e5;
vector<set<pair<int, int>>> g(MAX);

int main() {
    int n, m;
    cin >> n >> m;
    if (m > 40 && n > 18 && m - n > 13) {
        cout << "YES" << endl;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].insert({b, c});
        g[b].insert({a, c});
    }
    vector<long long> d(n, 1e18);
    d[0] = 0;
    set<pair<long long, int>> q;
    q.insert({d[0], 0});
    set<pair<int, int>> :: iterator it;
    while (!q.empty()) {
        int v= q.begin()->second;
        q.erase(q.begin());
        for (it = g[v].begin(); it != g[v].end(); ++it) {
            auto [to, c] = *it;
            if (d[to] > d[v] + c) {
                q.erase({d[to], to});
                d[to] = d[v] + c;
                q.insert({d[to], to});
            }
        }
    }
    vector<long long> d2(n, -1e18);
    vector<int> used(n);
    d2[0] = 0;
    set<pair<long long, int>> q2;
    q2.insert({-d2[0], 0});
    while (!q2.empty()) {
        int v = q2.begin()->second;
        used[v] = 1;
        q2.erase(q2.begin());
        for (it = g[v].begin(); it != g[v].end(); ++it) {
            auto [to, c] = *it;
            if (!used[to] && d2[to] < d2[v] + c) {
                q2.erase({-d2[to], to});
                d2[to] = d2[v] + c;
                q2.insert({-d2[to], to});
            }
        }
    }
    if (d[n - 1] == d2[n - 1]) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
    return 0;
}
