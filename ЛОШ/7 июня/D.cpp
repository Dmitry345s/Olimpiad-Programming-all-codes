#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge {
    int to, i;
};
int MAX = 1e5, h = 18;
vector<vector<edge>> g(MAX);
vector<vector<int>> up(MAX, vector<int> (h));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs (int v, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < h; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto [to, i] : g[v]) {
        if (to != p) {
            dfs(to, v);
        }
    }
    tout[v] = timer++;
}

bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
    if (upper(a, b)) {
        return a;
    }
    if (upper(b, a)) {
        return b;
    }
    for (int i = h - 1; i >= 0; --i) {
        if (!upper(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

vector<int> vs(MAX), c(MAX), s(MAX);
set<pair<int, pair<int, int>>> st;

void dfs2(int v, int a, int b, int p) {
    for (auto [to, i] : g[v]) {
        if (to != p && (upper(to, a) || upper(to, b))) {
            st.insert({vs[i], {i, 0}});
            dfs2(to, a, b, v);
        }
    }
}

int for_ans(long long r) {
    for (int i = 0; i < int(st.size()) + 1; ++i) {
        pair<int, pair<int, int>> m = *(st.begin());
        int j = m.second.first;
        if (m.second.second == -1) {
            return s[j];
        }
        if (c[j] > r) {
            return vs[j];
        }
        r -= c[j];
        st.erase(st.begin());
        st.insert({s[j], {j, -1}});
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b >> vs[i] >> c[i] >> s[i];
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    dfs(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        long long r;
        int a, b;
        cin >> a >> b >> r;
        --a; --b;
        int x = lca(a, b);
        st.clear();
        dfs2(x, a, b, up[x][0]);
        cout << for_ans(r) << endl;
    }
    return 0;
}
