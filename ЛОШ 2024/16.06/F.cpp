#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> a(MAX);
vector<int> h(MAX), ch(MAX, -1), h2(MAX);
vector<set<pair<int, int>>> h3(MAX);
vector<int> up(MAX), h4(MAX);

void dfs(int v, int p, int st = -1) {
    ch[v] = st;
    if (v != p) {
        h[v] = h[p] + a[v];
    }
    h2[v] = h2[p] + 1;
    for (int to : g[v]) {
        if (to == p) continue;
        if (v == p) {
            dfs(to, v, to);
        } else {
            dfs(to, v, st);
        }
    }
}

void dfs2(int v, int p) {
    h2[v] = h2[p] + 1;
    h3[v].insert({0, v});
    h4[v] = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
        h3[v].insert({h4[to] - 1, to});
        h4[v] = min(h4[v], h4[to] - 1);
    }
}

void dfs3(int v, int p) {
    if (p != v) {
        up[v] = max(0ll, max(up[p], -(*h3[p].begin()).first) + 1);
    } else {
        up[v] = 0;
    }
    for (int to : g[v]) {
        if (to == p) {
            continue;
        }
        h3[v].erase({h4[to] - 1, to});
        dfs3(to, v);
        h3[v].insert({h4[to] - 1, to});
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] != 1) flag = 0;
    }
    if (n <= 2000) {
        int rrans = 0;
        for (int _ = 0; _ < n; ++_) {
            h.assign(n, 0);
            ch.assign(n, -1);
            h2.assign(n, 0);
            h2[_] = -1;
            dfs(_, _);
            //map<int, int> mp;
            vector<array<int, 3>> all;
            for (int i = 0; i < n; ++i) {
                all.push_back({h2[i], h[i], ch[i]});
            }
            sort(all.rbegin(), all.rend());
            int now = 0;
            int rans = a[_];
            for (int i = n - 1; i > 0; --i) {
                map<int, vector<int>> mp;
                while (all[now][0] == i) {
                    mp[all[now][2]].push_back(all[now][1]);
                    now++;
                }
                vector<int> tr;
                for (auto [key, val] : mp)  {
                    sort(val.rbegin(), val.rend());
                    //cout << _ << " " << key << " " << i << " " << val[0] << endl;
                    tr.push_back(val[0]);
                }
                sort(tr.rbegin(), tr.rend());
                int ans = a[_];
                int l = 0;
                while (l < (int)tr.size() && tr[l] >= 0) {
                    ans += tr[l];
                    l++;
                }
                if (l < 2 && (int)tr.size() > 1) {
                    while (l < 2) {
                        ans += tr[l];
                        l++;
                    }
                }
                if (l >= 2) {
                    rans = max(rans, ans);
                }
            }
            //cout << rans << endl;
            rrans = max(rans, rrans);
        }
        cout << rrans << endl;
    } else if (flag) {
        dfs2(0, 0);
        dfs3(0, 0);
        int rans = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> to_ans = {up[i]};
            //cout << up[i] << endl;
            for (auto [val, u] : h3[i]) {
                to_ans.push_back(-val);
            }
            sort(to_ans.rbegin(), to_ans.rend());
            int ans = 0;
            for (int j = 1; j < (int)to_ans.size(); ++j) {
                ans = max(ans, to_ans[j] * (j + 1) + 1);
            }
            rans = max(rans, ans);
        }
        cout << rans << endl;
    }
    return 0;
}
