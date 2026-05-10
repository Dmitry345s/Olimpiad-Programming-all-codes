#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

using namespace std;

vector<int> cnt(4);
int n, m;
vector<pair<int, int>> st;
vector<int> used;

void dfs(int p) {
    //cout << x << " " << y << endl;
    auto [x, y] = st[p];
    if (x == 1) {
        cnt[0]++;
    }
    if (y == 1) {
        cnt[1]++;
    }
    if (x == n) {
        cnt[2]++;
    }
    if (y == m) {
        cnt[3]++;
    }
    used[p] = 1;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int u = lower_bound(st.begin(), st.end(), pair<int, int>{x + i, y + j}) - st.begin();
            if (u < st.size() && used[u] == 0 && st[u] == pair<int, int>{x + i, y + j}) {
                dfs(u);
            }
        }
    }
}

bool ch(vector<pair<int, int>> ks, int x) {
    st.clear();
    used.assign(x, 0);
    for (int i = 0; i < x; ++i) {
        st.push_back(ks[i]);
    }
    sort(st.begin(), st.end());
    int flag = 1;
//cout << (st.find({2, 2}) != st.end()) << endl;
    for (int i = 0; i < x; ++i) {
        if (used[i]) continue;
        cnt.assign(4, 0);
        dfs(i);
        //cout << "!" << endl;
        if (cnt[0] && cnt[1] || cnt[0] && cnt[2] || cnt[1] && cnt[3] || cnt[3] && cnt[2]) {
            flag = 0;
            break;
        }
    }
    return flag;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> n >> m >> k;
    vector<pair<int, int>> ks(k);
    for (int i = 0; i < k; ++i) {
        cin >> ks[i].first >> ks[i].second;
    }
    int l = 0, r = k + 1;
    while (l + 1 < r) {
        //cout << l << " " << r << endl;
        int m = (l + r) / 2;
        if (ch(ks, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    for (int i = 0; i < k; ++i) {
        if (i < l) {
            cout << "Success!" << endl;
        } else {
            cout << "Defeat!" << endl;
        }
    }
    return 0;
}
