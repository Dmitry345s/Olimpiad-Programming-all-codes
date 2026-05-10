#include<bits/stdc++.h>

using namespace std;

const int K = 2000;
const int MAX = 1e5 + 5;
int cnt[MAX];
int cnt2[MAX];

void add(int y) {
    cnt[y]++;
    cnt2[y / K]++;
}

void del(int y) {
    cnt[y]--;
    cnt2[y / K]--;
}

bool cmp(array<int, 5> a, array<int, 5> b) {
    if (b[0] / K == a[0] / K) {
        if (a[1] / K == b[1] / K) {
            if (a[2] == b[2]) {
                return a[4] < b[4];
            }
            return a[2] < b[2];
        }
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> nb = a;
    vector<array<int, 3>> go;
    vector<array<int, 5>> qs;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x, y;
            cin >> l >> r >> x >> y;
            --l;
            for (int j = l; j < r; ++j) {
                if (nb[j] == x) {
                    nb[j] = y;
                    go.push_back({j, x, y});
                }
            }
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            qs.push_back({(int)go.size(), l, r, k, i});
        }
    }
    sort(qs.begin(), qs.end(), cmp);
    vector<int> ans(m);
    int nt = 0, l = 0, r = 0;
    nb = a;
    for (auto [t, ql, qr, qk, in] : qs) {
        while (nt < t) {
            auto [in, x, y] = go[nt];
            if (l <= in && in < r) {
                del(x);
                add(y);
            }
            nb[in] = y;
            ++nt;
        }
        while (nt > t) {
            --nt;
            auto [in, x, y] = go[nt];
            if (l <= in && in < r) {
                del(y);
                add(x);
            }
            nb[in] = x;
        }
        while (l > ql) {
            --l;
            add(nb[l]);
        }
        while (r < qr) {
            add(nb[r]);
            r++;
        }
        while (l < ql) {
            del(nb[l]);
            l++;
        }
        while (r > qr) {
            --r;
            del(nb[r]);
        }
        int sum = 0;
        int fl = -1;
        for (int i = 0; i < MAX; ++i) {
            sum += cnt2[i];
            if (sum >= qk) {
                fl = i;
                break;
            }
        }
        sum -= cnt2[fl];
        /*cout << in << endl;
        cout << l << " " << r << " " << nt << endl;
        for (int i = 0; i < 5; ++i) {
            cout << cnt[i] << " ";
        }
        cout << endl;*/
        for (int i = K * fl; i < MAX; ++i) {
            sum += cnt[i];
            if (sum >= qk) {
                ans[in] = i;
                break;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        if (ans[i] != 0) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
