#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int MAX = 1e5 + 10;
vector<int> g[MAX], h[MAX];
int sz[MAX];
const ull P = 1791791791;
ull hs1[MAX], hs2[MAX];

ull gh(int v) {
    ull ans = 0;
    sz[v] = 1;
    vector<int> ty;
    for (int to : g[v]) {
        ty.push_back(gh(to));
        sz[v] += sz[to];
    }
    ty.push_back(sz[v]);
    sort(ty.begin(), ty.end());
    for (int i = 0; i < (int)ty.size(); ++i) {
        ans *= P;
        ans += ty[i];
    }
    hs1[v] = ans;
    return ans;
}

ull gh2(int v) {
    ull ans = 0;
    sz[v] = 1;
    vector<int> ty;
    for (int to : h[v]) {
        ty.push_back(gh2(to));
        sz[v] += sz[to];
    }
    ty.push_back(sz[v]);
    sort(ty.begin(), ty.end());
    for (int i = 0; i < (int)ty.size(); ++i) {
        ans *= P;
        ans += ty[i];
    }
    hs2[v] = ans;
    return ans;
}

int dfs1(int r1, int r2) {
    set<pair<int, int>> st;
    for (int to : h[v]) {
        st.insert({hs2[to], to});
    }
    for (int to : g[v]) {

    }
    do {

    } while (next_permutation(bb.begin(), bb.end());
}

signed main() {
    int _, __;
    cin >> _ >> __;
    while (_--) {
        int n;
        cin >> n;
        int r = -1;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            if (p == -1) {
                r = i;
                continue;
            }
            --p;
            g[p].push_back(i);
        }
        int n2;
        cin >> n2;
        for (int i = 0; i < n2; ++i) {
            h[i].clear();
        }
        int r2 = -1;
        for (int i = 0; i < n2; ++i) {
            int p;
            cin >> p;
            if (p == -1) {
                r2 = i;
                continue;
            }
            --p;
            h[p].push_back(i);
        }
        ull t1 = gh(r);
        ull t2 = gh2(r2);
        if (t1 == t2) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
