#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

vector<int> g[MAX];
int d[MAX];
int a[MAX];

void bfs(int v, int n) {
    fill(d, d + n, MAX);
    d[v] = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
}

int tree[MAX];

void add(int i, int x) {
    for (; i < MAX; i |= (i + 1)) {
        tree[i] += x;
    }
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

int solve(int u, int v, int n) {
    bfs(u, n);
    vector<int> dist(n);
    for (int i = 0; i < n; ++i) {
        dist[i] = d[i];
    }
    bfs(v, n);
    int rans = 2 * n;
    for (int i = 0; i < n; ++i) {
        rans = min(rans, dist[i] + d[i]);
    }
    return rans;
}

signed main() {
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> ls(n, -1);
    vector<int> rs(n, -1);
    vector<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.back().first <= a[i]) {
            rs[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({a[i], i});
    }
    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && st.back().first <= a[i]) {
            ls[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({a[i], i});
    }
    for (int i = 0; i < n; ++i) {
        if (ls[i] != -1) {
            g[i].push_back(ls[i]);
        }
        if (rs[i] != -1) {
            g[i].push_back(rs[i]);
        }
    }
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        cout << min(solve(u, v, n), solve(v, u, n)) - 1 << endl;
    }
    return 0;
}
