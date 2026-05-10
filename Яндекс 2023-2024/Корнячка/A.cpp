#include<bits/stdc++.h>

using namespace std;

int k = 315;
int MAX = 1e5 + 1;
vector<int> a(MAX);
vector<pair<int, int>> b(MAX);
vector<int> used(MAX);

void get_next(int now, int num, int n) {
    used[now] = 1;
    if (now + a[now] >= min(k * (num + 1), n)) {
        b[now] = {0, now};
    } else {
        if (!used[a[now] + now]) {
            get_next(a[now] + now, num, n);
        }
        b[now] = b[now + a[now]];
        b[now].first++;
    }
}

void build_block(int num, int n) {
    for (int i = num * k; i < min((num + 1) * k, n); ++i) {
        used[i] = 0;
    }
    for (int i = num * k; i < min((num + 1) * k, n); ++i) {
        if (!used[i]) {
            get_next(i, num, n);
        }
    }
}

pair<int, int> get(int i, int n) {
    pair<int, int> ans = b[i];
    //cout << i << " " << ans.first << " " << ans.second << endl;
    while (ans.second + a[ans.second] < n) {
        ans.first += b[a[ans.second] + ans.second].first + 1;
        ans.second = b[a[ans.second] + ans.second].second;
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i += k) {
        build_block(i / k, n);
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int j, b;
            cin >> j >> b;
            --j;
            a[j] = b;
            build_block(j / k, n);
        } else {
            int j;
            cin >> j;
            --j;
            auto ans = get(j, n);
            cout << ans.second + 1 << " " << ans.first + 1 << '\n';
        }
    }
    return 0;
}
