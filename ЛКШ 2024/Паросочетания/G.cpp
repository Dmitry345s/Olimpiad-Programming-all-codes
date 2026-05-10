#include<bits/stdc++.h>

using namespace std;

const int MAX = 205;
vector<vector<int>> g(MAX);
vector<int> used(MAX), now_pair(MAX, -1);
vector<int> to_sort(MAX);
int timer = 1;

bool cmp(int a, int b) {
    if (to_sort[a] == to_sort[b]) {
        return a < b;
    }
    return to_sort[a] > to_sort[b];
}

bool try_kuhn(int v) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1) {
            now_pair[to] = v;
            return 1;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}
signed main() {
    int m, k, n;
    cin >> m >> k >> n;
    vector<vector<int>> to_ed(m, vector<int> (k, 1));
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        b -= m;
        to_ed[a][b] = 0;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            if (to_ed[i][j]) {
                //cout << "! " << i << " " << j + m << endl;
                g[i].push_back(j + m);
            }
        }
    }
    int q;
    cin >> q;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < q; ++i) {
        int v;
        cin >> v;
        --v;
        if (v < m) {
            cnt1++;
        } else {
            cnt2++;
        }
        to_sort[v] = 1;
    }
    if (cnt1 > n || cnt2 > n) {
        cout << "NO" << endl;
        return 0;
    }
    vector<int> ord;
    for (int i = 0; i < m; ++i) {
        sort(g[i].begin(), g[i].end(), cmp);
        ord.push_back(i);
    }
    sort(ord.begin(), ord.end(), cmp);
    for (int i = 0; i < m; ++i) {
        //cout << ord[i] << " ";
        if (timer - 1 == n) break;
        if (try_kuhn(ord[i])) {
            timer++;
        }
    }
    if (timer - 1 != n) {
        cout << "NO" << endl;
        return 0;
    }
    vector<int> to_com(m + k);
    for (int i = m; i < m + k; ++i) {
        if (now_pair[i] == -1 && to_sort[i] == 1) {
            cout << "NO" << endl;
            return 0;
        }
        if (now_pair[i] != -1) {
            to_com[now_pair[i]] = 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (to_sort[i] == 1 && to_com[i] == 0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    vector<pair<int, int>> ans;
    for (int i = m; i < m + k; ++i) {
        if (now_pair[i] != -1) {
            ans.push_back({now_pair[i], i});
        }
    }
    cout << "YES" << endl;
    //cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }
    return 0;
}
