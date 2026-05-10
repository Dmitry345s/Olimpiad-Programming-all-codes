#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5 + 1;
vector<vector<int>> all(1);
vector<int> rans(1);
vector<int> l(1);
vector<int> used(1);

void split(int x) {
    int tr = 0;
    for (int i = 0; i < (int)l.size(); ++i) {
        if (!used[i]) continue;
        if (l[i] + (int)all[i].size() - 1 == x) {
            return;
        }
        if (l[i] <= x && x < l[i] + (int)all[i].size() - 1) {
            tr = i;
            break;
        }
    }
    vector<int> n1, n2;
    int r1 = 2e9, r2 = 2e9;
    for (int i = l[tr]; i <= x; ++i) {
        n1.push_back(all[tr][i - l[tr]]);
        r1 = min(r1, n1.back());
    }
    for (int i = x + 1; i < (int)all[tr].size() + l[tr]; ++i) {
        n2.push_back(all[tr][i - l[tr]]);
        r2 = min(r2, n2.back());
    }
    used[tr] = 0;
    all.push_back(n1);
    rans.push_back(r1);
    all.push_back(n2);
    rans.push_back(r2);
    used.push_back(1);
    used.push_back(1);
    l.push_back(l[tr]);
    l.push_back(x + 1);
}

void add(int j, int x) {
    for (int i = 0; i < (int)all.size(); ++i) {
        if (!used[i]) continue;
        if (l[i] + (int)all[i].size() - 1 == j) {
            all[i].push_back(x);
            rans[i] = min(rans[i], x);
        } else if (l[i] > j) {
            l[i]++;
        }
    }
}

int get(int j, int k) {
    int ans = 2e9;
    for (int i = 0; i < (int)all.size(); ++i) {
        if (!used[i]) continue;
        if (j <= l[i] && l[i] + (int)all[i].size() - 1 <= k) {
            ans = min(ans, rans[i]);
        }
    }
    return ans;
}

void rebuild(int n) {
    int u = sqrt(n);
    vector<int> a(n + 3, 2e9);
    for (int i = 0; i < (int)all.size(); ++i) {
        if (!used[i]) continue;
        for (int j = l[i]; j < (int)all[i].size() + l[i]; ++j) {
            a[j] = all[i][j - l[i]];
        }
    }
    all.clear();
    rans.clear();
    l.clear();
    used.clear();
    int r1 = 2e9;
    vector<int> now;
    int last = 0;
    for (int i = 0; i < n + 1; ++i) {
        if (a[i] == 2e9 && i != 0) break;
        if (i % u == 0 && now.size() != 0) {
            all.push_back(now);
            rans.push_back(r1);
            l.push_back(last);
            used.push_back(1);
            now.clear();
            r1 = 2e9;
            last = i;
        }
        now.push_back(a[i]);
        r1 = min(r1, now.back());
    }
    if (now.size() != 0) {
        all.push_back(now);
        rans.push_back(r1);
        l.push_back(last);
        used.push_back(1);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    rans[0] = 2e9;
    all[0].push_back(2e9);
    l[0] = 0;
    used[0] = 1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int j, x;
            cin >> j >> x;
            split(j);
            add(j, x);
            cnt += 2;
        } else {
            int j, k;
            cin >> j >> k;
            split(j - 1);
            split(k);
            cout << get(j, k) << '\n';
            cnt += 4;
        }
        if (cnt % 450 == 0 && cnt != 0) {
            rebuild(cnt);
        }
    }
    return 0;
}
