#include<bits/stdc++.h>

using namespace std;

struct Node {
    int c;
    Node* pref = nullptr;
    Node* next = nullptr;
    Node (int c1) {
        c = c1;
    }
};

signed main() {
    int r, s;
    cin >> r >> s;
    vector<vector<int>> a(r, vector<int> (s));
    vector<Node*> b(s);
    set<array<int, 3>> st;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            cin >> a[i][j];
        }
    }
    int l = 0;
    while (l < s) {
        int left = l;
        while (l < s && a[0][left] == a[0][l]) {
            l++;
        }
        st.insert({left, l - 1, a[0][left]});
    }
    int qs;
    cin >> qs;
    for (int i = 0; i < qs; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u; --v;
        auto it = st.upper_bound({v, (int)1e9, (int)1e9});
        --it;
        int left = (*it)[0], right = (*it)[1];
        //cout << left << " " << right << endl;
        if (it != st.begin()) {
            --it;
            if ((*it)[2] == c) {
                left = (*it)[0];
            }
            ++it;
        }
        ++it;
        if (it != st.end()) {
            if ((*it)[2] == c) {
                right = (*it)[1];
            }
            --it;
        }
        //cout << left << " " << right << endl;
        int k = left;
        while (k <= right) {
            auto it2 = st.lower_bound({k, -1, -1});
            k = (*it2)[1] + 1;
            st.erase(it2);
        }
        st.insert({left, right, c});
    }
    for (auto [l, r, c] : st) {
        for (int j = l; j <= r; ++j) {
            a[0][j] = c;
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
