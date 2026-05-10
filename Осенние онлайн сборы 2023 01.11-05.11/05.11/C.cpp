#include<bits/stdc++.h>

using namespace std;

int MAX = 1e6;
vector<int> ps(MAX, 1e9);

void st(vector<int> a, int n) {
    vector<vector<int>> up(MAX);
    for (int i = 0; i < n; ++i) {
        for (int j = a[i]; j < MAX; j += a[i]) {
            up[j].push_back(i);
        }
    }
    set<pair<int, int>> st;
    vector<int> last(n);
    for (int i = 0; i < n; ++i) {
        st.insert({0, a[i]});
        last[i] = 0;
    }
    ps[0] = 0;
    for (int i = 1; i < MAX; ++i) {
        for (int j = 0; j < (int)up[i].size(); ++j) {
            st.erase({ps[last[up[i][j]]], a[up[i][j]]});
            last[up[i][j]] = i;
            st.insert({ps[last[up[i][j]]], a[up[i][j]]});
        }
        ps[i] = min(ps[i], (*st.begin()).first + 1);
        for (int j = 0; j < (int)up[i].size(); ++j) {
            st.erase({ps[last[up[i][j]]], a[up[i][j]]});
            last[up[i][j]] = i;
            st.insert({ps[last[up[i][j]]], a[up[i][j]]});
        }
    }
}

int my_get(vector<int> & a, int p) {
    if (p == 0) {
        return 0;
    }
    int minm = p;
    for (int i = 0; i < (int)a.size(); ++i) {
        minm = min(minm, p - p % a[i]);
    }
    if (minm == p) {
        return 1e9;
    }
    return min((int)1e9, 1 + my_get(a, minm));
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (q == 1) {
        int p;
        cin >> p;
        cout << my_get(a, p);
        return 0;
    }
    st(a, n);
    for (int i = 0; i < q; ++i) {
        int p;
        cin >> p;
        if (ps[p] == 1e9) {
            cout << "oo" << endl;
        } else {
            cout << ps[p] << endl;
        }
    }
    return 0;
}
