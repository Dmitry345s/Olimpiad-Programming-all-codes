#include<bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int MAX = 1e5 + 1;

vector<int> tree[4 * MAX];
int c[MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {c[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    for (auto t : tree[2 * v]) {
        tree[v].push_back(t);
    }
    for (auto t : tree[2 * v + 1]) {
        tree[v].push_back(t);
    }
    sort(tree[v].begin(), tree[v].end());
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin();
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr, x) + get(2 * v + 1, m, r, ql, qr, x);
}

signed main() {
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    vector<pair<int, int>> sg(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
        sg[i] = {a[i][0], a[i][1]};
    }
    sort(a.begin(), a.end());
    vector<int> stup(n);
    vector<int> jur(n);
    vector<array<int, 5>> qs;
    for (int i = 0; i < n; ++i) {
        c[i] = a[i][1];
        //cout << c[i] << " ";
    }
    vector<int> flag(n, 1);
    for (int i = 0; i < n; ++i) {
        cin >> stup[i];
        --stup[i];
        if (stup[i] != -1) {
            //stup[i]--;
            if (sg[stup[i]].first <= sg[i].first && sg[i].second <= sg[stup[i]].second) {
                int l = upper_bound(a.begin(), a.end(), array<int, 3>{sg[stup[i]].first, -INF, -INF}) - a.begin();
                int r = upper_bound(a.begin(), a.end(), array<int, 3>{sg[i].first, INF, INF}) - a.begin();
                qs.push_back({l, r, sg[i].second, sg[stup[i]].second + 1, i});
            } else {
                flag[i] = 0;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cin >> jur[i];
        jur[i]--;
        if (jur[i] == -1 && stup[i] != -1) {
            flag[i] = 0;
        }
        if (jur[i] != -1 && stup[i] == -1) {
            flag[i] = 0;
        }
    }
    build(1, 0, n);
    for (int i = 0; i < (int)qs.size(); ++i) {
        //cout << qs[i][0] << " " << qs[i][1] << " " << qs[i][2] << " " << qs[i][3] << " " << qs[i][4] << endl;
        int cnt1 = get(1, 0, n, qs[i][0], qs[i][1], qs[i][2]);
        int cnt2 = get(1, 0, n, qs[i][0], qs[i][1], qs[i][3]);
        //cout << cnt1 << endl;
        //cout << cnt2 << endl;
        if (cnt2 - cnt1 != 2) {
            flag[qs[i][4]] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (flag[i]) {
            cout << "OK" << endl;
        } else {
            cout << "WA" << endl;
        }
    }
    return 0;
}
