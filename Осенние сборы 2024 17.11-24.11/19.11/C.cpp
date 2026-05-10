#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> sz(MAX);
vector<int> ps(MAX);

void dfs(int v, int p) {
    sz[v] = 1;
    ps[v] = p;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
}

vector<int> ans;
int now = 0;

void f(int v, int p) {
    ans[now] = v;
    int cnt = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        now++;
        f(to, v);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
        if ((int)g[i].size() == 1) cnt++;
    }
    if (n <= 1000) {
        vector<int> all;
        for (int i = 0; i < n; ++i) {
            ans.assign(n, -1);
            now = 0;
            f(i, -1);
            for (int i = 0; i < n; ++i) {
                all.push_back(ans[i]);
            }
        }
        for (int i = 0; i < q; ++i) {
            int k;
            cin >> k;
            --k;
            cout << k / n + 1 << " " << all[k] + 1 << endl;
        }
        return 0;
    }
    if (cnt == 2) {
        vector<int> pos(n);
        int st = -1;
        for (int i = 0; i < n; ++i) {
            if ((int)g[i].size() == 1) {
                st = i;
                break;
            }
        }
        vector<int> vec(n);
        vec[0] = st;
        int pref = -1;
        for (int i = 1; i < n; ++i) {
            for (int to : g[st]) {
                if (to == pref) continue;
                pref = st;
                st = to;
                vec[i] = to;
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            pos[vec[i]] = i;
        }
        for (int i = 0; i < q; ++i) {
            long long k;
            cin >> k;
            --k;
            int fst = k / n;
            int j = pos[fst];
            if (j == 0) {
                cout << fst + 1 << " " << vec[j + k % n] + 1 << endl;
                continue;
            }
            if (j == n - 1) {
                cout << fst + 1 << " " << vec[j - k % n] + 1 << endl;
                continue;
            }
            int x = k % n;
            if (vec[j - 1] < vec[j + 1]) {
                if (j < x) {
                    x -= j;
                    cout << fst + 1 << " " << vec[j + x] + 1 << endl;
                } else {
                    cout << fst + 1 << " " << vec[j - x] + 1 << endl;
                }
            } else {
                if (n - 1 - j < x) {
                    x -= n - 1 - j;
                    cout << fst + 1 << " " << vec[j - x] + 1 << endl;
                } else {
                    cout << fst + 1 << " " << vec[j + x] + 1 << endl;
                }
            }
        }
        return 0;
    }
    if (cnt == n - 1) {
        int c = -1;
        for (int i = 0; i < n; ++i) {
            if ((int)g[i].size() != 1) {
                c = i;
            }
        }
        vector<int> u;
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            if (i == c) continue;
            u.push_back(i);
            pos[i] = (int)u.size() - 1;
        }
        for (int i = 0; i < q; ++i) {
            long long k;
            cin >> k;
            k--;
            int fst = k / n;
            int x = k % n;
            if (x == 0) {
                cout << fst + 1 << " " << fst + 1 << endl;
                continue;
            }
            if (fst == c) {
                cout << fst + 1 << " " << u[x - 1] + 1 << endl;
                continue;
            }
            if (x == 1) {
                cout << fst + 1 << " " << c + 1 << endl;
                continue;
            }
            x -= 2;
            if (pos[fst] <= x) {
                x++;
            }
            cout << fst + 1 << " " << u[x] + 1 << endl;

        }
        return 0;
    }
    ans.assign(n, -1);
    now = 0;
    f(0, -1);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        --k;
        cout << 1 << " " << ans[k] + 1 << endl;
    }
    return 0;
}
