#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

int MAX = 1e5 + 3;
vector<vector<pair<int, int>>> g(MAX);
string s;
mt19937 rnd(time(0));

void dfs(int v, int p = -1) {
    for (auto[to, c] : g[v]) {
        if (to == p) continue;
        s.push_back(c);
        dfs(to, v);
    }
}

int mod = 1e9 + 7;
int b = 179;
vector<ull> pows(2 * MAX + 1), h(2 * MAX + 1);

ull get(int i, int len) {
    ull ans = h[i + len] - h[i] * pows[len];
    return ans;
}

int tr(int i1, int i2, int n) {
    int l = -1, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (get(i1, m) != get(i2, m)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

signed main() {
    int n, m;
    cin >> n >> m;
    //char minm = char((int)'z' + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        --a; --b;
        //minm = min(minm, c);
        g[a].push_back({b, c});
    }
    dfs(0);
    string t = s + s;
    pows[0] = 1;
    for (int i = 1; i < pows.size(); ++i) {
        pows[i] = pows[i - 1] * b;
    }
    for (int i = 1; i < t.size(); ++i) {
        int c = (int)t[i - 1] - 97 + 1;
        h[i] = h[i - 1] * b + c;
    }
    int minm = 0;
    for (int i = 1; i < s.size(); ++i) {
        int j = tr(i, minm, n - 1);
        if (t[i + j - 1] < t[minm + j - 1]) {
            minm = i;
        }
    }
    string s2;
    for (int i = minm; i < minm + n - 1; ++i) {
        s2.push_back(t[i]);
    }
    cout << s2 << endl;
    /*vector<int> u;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == minm) {
            u.push_back(i);
        }
    }
    //cout << 0 << endl;
    set<string> st;
    for (int i = u.size() / 3; i < u.size(); ++i) {
        int j = i;
        //cout << i << endl;
        int k = u[j];
        string s2;
        for (int l = k; l < k + n - 1; ++l) {
            s2.push_back(s[l % s.size()]);
        }
        st.insert(s2);
    }
    auto it = st.begin();
    cout << *it << endl;*/
    return 0;
}
