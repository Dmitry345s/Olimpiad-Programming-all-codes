#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e9, MOD = 1e9 + 7, LN = 19, MAX = 3e5;

vector<array<int, 2>> bfs (vector<vector<int>> g, int n) {
    vector<array<int, 2>> ans(n, {INF, INF});
    queue<int> q;
    ans[0][0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            int d = ans[v][0] + 1;
            int d2 = ans[v][1] + 1;
            if (d < ans[to][1]) {
                ans[to][1] = d;
                q.push(to);
            }
            if (d2 < ans[to][0]) {
                ans[to][0] = d2;
                q.push(to);
            }
        }
    }
    return ans;
}

int tree[4 * MAX], tree2[4 * MAX];

int um(int a, int b) {
    return (1ll * a * b) % MOD;
}

void update(int in, int x) {
    int v = in + (1 << (LN - 1));
    tree[v] += x;
    while (v != 1) {
        v /= 2;
        tree[v] = um(tree[2 * v], tree[2 * v + 1]);
    }
}

int get(int l, int r) {
    l = l + (1 << (LN - 1));
    r = r + (1 << (LN - 1));
    int lans = 1, rans = 1;
    while (l <= r) {
        if (l % 2) {
            lans = um(lans, tree[l]);
        }
        l = (l + 1) / 2;
        if (r % 2 == 0) {
            rans = um(rans, tree[r]);
        }
        r = (r - 1) / 2;
    }
    return um(lans, rans);
}

void update2(int in, int x) {
    int v = in + (1 << (LN - 1));
    tree2[v] += x;
    while (v != 1) {
        v /= 2;
        tree2[v] = um(tree2[2 * v], tree2[2 * v + 1]);
    }
}

int get2(int l, int r) {
    l = l + (1 << (LN - 1));
    r = r + (1 << (LN - 1));
    int lans = 1, rans = 1;
    while (l <= r) {
        if (l % 2) {
            lans = um(lans, tree2[l]);
        }
        l = (l + 1) / 2;
        if (r % 2 == 0) {
            rans = um(rans, tree2[r]);
        }
        r = (r - 1) / 2;
    }
    return um(lans, rans);
}

signed main() {
    int k;
    cin >> k;
    vector<array<int, 3>> now1, now2;
    for (int i = 0; i < k; ++i) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        for (int j = 0; j < m; ++j) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<array<int, 2>> dist = bfs(g, n);
        for (int j = 0; j < n; ++j) {
            //cout << dist[j][0] << " " << dist[j][1] << endl;
            now1.push_back({dist[j][0], i, dist[j][1]});
            now2.push_back({dist[j][1], i, dist[j][0]});
        }
        //cout << endl;
    }
    sort(now1.begin(), now1.end());
    int j = 0;
    int last = 0, last2 = 0;
    multiset<pair<int, int>> st;
    int ans = 0;
    for (int i = 0; i < MAX; i += 2) {
        while ((int)st.size() > 0 && (*st.begin()).first <= i) {
            update2((*st.begin()).second, 1);
            st.erase(st.begin());
        }
        last2 = get2(0, k - 1);
        while (j < (int)now1.size() && now1[j][0] <= i) {
            update(now1[j][1], 1);
            st.insert({now1[j][2], now1[j][1]});
            j++;
        }
        int now = get(0, k - 1) - last;
        if (now < 0) now += MOD;
        //cout << now << endl;
        while ((int)st.size() > 0 && (*st.begin()).first <= i) {
            update2((*st.begin()).second, 1);
            st.erase(st.begin());
        }
        int nowch = get2(0, k - 1) - last2;
        if (nowch < 0) nowch += MOD;
        now -= nowch;
        if (now < 0) now += MOD;
        ans += um(now, i);
        ans %= MOD;
        last = get(0, k - 1);
    }
    //cout << ans << endl;
    fill(tree, tree + 4 * MAX, 0);
    fill(tree2, tree2 + 4 * MAX, 0);
    st.clear();
    last = 0;
    j = 0;
    last2 = 0;
    sort(now2.begin(), now2.end());
    for (int i = 1; i < MAX; i += 2) {
        while ((int)st.size() > 0 && (*st.begin()).first <= i) {
            update2((*st.begin()).second, 1);
            st.erase(st.begin());
        }
        last2 = get2(0, k - 1);
        while (j < (int)now2.size() && now2[j][0] <= i) {
            update(now2[j][1], 1);
            st.insert({now2[j][2], now2[j][1]});
            j++;
        }
        int now = get(0, k - 1) - last;
        if (now < 0) now += MOD;
        while ((int)st.size() > 0 && (*st.begin()).first <= i) {
            update2((*st.begin()).second, 1);
            st.erase(st.begin());
        }
        int nowch = get2(0, k - 1) - last2;
        if (nowch < 0) nowch += MOD;
        now -= nowch;
        if (now < 0) now += MOD;
        ans += um(now, i);
        ans %= MOD;
        last = get(0, k - 1);
    }
    cout << ans << endl;
    return 0;
}
/*
2

2 2
1 2
2 2

3 3
1 2
2 3
3 3
*/
