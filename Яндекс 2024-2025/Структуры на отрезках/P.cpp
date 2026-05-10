#include<bits/stdc++.h>

using namespace std;

const int K1 = 3000, K2 = 3000;

bool cmp(array<int, 4> a, array<int, 4> b) {
    if (a[0] / K1 == b[0] / K1) {
        if (a[2] / K2 == a[2] / K2) {
            return a[1] < b[1];
        }
        return a[2] < b[2];
    }
    return a[0] < b[0];
}

const int MAX = 5e5 + 2, K3 = 700;
int cnt[MAX];
int cnt2[MAX];

void add(int a) {
    cnt2[a / K3] -= (cnt[a] == 0);
    cnt[a]++;
    cnt2[a / K3] += (cnt[a] == 0);
}

void del(int a) {
    cnt2[a / K3] -= (cnt[a] == 0);
    cnt[a]--;
    cnt2[a / K3] += (cnt[a] == 0);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<array<int, 3>> dif;
    vector<array<int, 4>> qs;
    vector<int> b = a;
    for (int i = 0; i < q; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r;
            cin >> l >> r;
            --l;
            qs.push_back({l, r, (int)dif.size(), i});
        } else {
            int in, x;
            cin >> in >> x;
            --in;
            dif.push_back({in, x, b[in]});
            b[in] = x;
        }
    }
    b = a;
    sort(qs.begin(), qs.end(), cmp);
    int t = 0, l = 0, r = 0;
    fill(cnt2, cnt2 + MAX, K3);
    vector<int> ans(q, -1);
    for (int _ = 0; _ < (int)qs.size(); ++_) {
        auto [ls, rs, ts, is] = qs[_];
        //cout << ls << " " << rs << " " << is << " " << ts << " " << l << " " << r << " " << t << endl;
        while (t < ts) {
            if (l <= dif[t][0] && dif[t][0] < r) {
                del(dif[t][2]);
                add(dif[t][1]);
            }
            b[dif[t][0]] = dif[t][1];
            t++;
        }
        while (t > ts) {
            t--;
            if (l <= dif[t][0] && dif[t][0] < r) {
                del(dif[t][1]);
                add(dif[t][2]);
            }
            b[dif[t][0]] = dif[t][2];
        }
        while (r < rs) {
            add(b[r]);
            r++;
        }
        while (l > ls) {
            l--;
            add(b[l]);
        }
        while (r > rs) {
            r--;
            del(b[r]);
        }
        while (l < ls) {
            del(b[l]);
            l++;
        }
        for (int i = 0; i < MAX; ++i) {
            if (cnt2[i] != 0) {
                for (int j = i * K3; j < MAX; ++j) {
                    if (cnt[j] == 0) {
                        ans[is] = j;
                        break;
                    }
                }
                break;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i] != -1) {
            cout << ans[i] << " ";
        }
    }
    cout << endl;
    return 0;
}
