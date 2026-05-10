#include<bits/stdc++.h>

using namespace std;

const int K = 2000;

bool cmp(array<int, 4> a, array<int, 4> b) {
    if (a[0] / K == b[0] / K) {
        if (a[1] / K == b[1] / K) {
            return a[2] < b[2];
        }
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

const int MAX = 3e5;
int cnt[MAX], cnt2[MAX];

void add(int x) {
    cnt2[cnt[x]]--;
    cnt[x]++;
    cnt2[cnt[x]]++;
}

void del(int x) {
    cnt2[cnt[x]]--;
    cnt[x]--;
    cnt2[cnt[x]]++;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> zip;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        zip.push_back(a[i]);
    }
    vector<int> b = a;
    int t = 0;
    vector<array<int, 4>> qs;
    vector<array<int, 3>> news;
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            qs.push_back({t, l, r, i});
        } else {
            int j, x;
            cin >> j >> x;
            --j;
            news.push_back({b[j], x, j});
            b[j] = x;
            zip.push_back(x);
            t++;
        }
    }
    sort(qs.begin(), qs.end(), cmp);
    sort(zip.begin(), zip.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(zip.begin(), zip.end(), a[i]) - zip.begin();
    }
    for (int i = 0; i < (int)news.size(); ++i) {
        news[i][0] = lower_bound(zip.begin(), zip.end(), news[i][0]) - zip.begin();
        news[i][1] = lower_bound(zip.begin(), zip.end(), news[i][1]) - zip.begin();
    }
    vector<int> ans(q, -1);
    t = 0;
    int l = 0;
    int r = 0;
    for (int i = 0; i < (int)qs.size(); ++i) {
        while (r < qs[i][2]) {
            add(a[r]);
            r++;
        }
        while (l > qs[i][1]) {
            l--;
            add(a[l]);
        }
        while (r > qs[i][2]) {
            r--;
            del(a[r]);
        }
        while (l < qs[i][1]) {
            del(a[l]);
            l++;
        }
        while (t < qs[i][0]) {
            if (l <= news[t][2] && news[t][2] < r) {
                del(news[t][0]);
                add(news[t][1]);
            }
            a[news[t][2]] = news[t][1];
            t++;
        }
        while (t > qs[i][0]) {
            t--;
            if (l <= news[t][2] && news[t][2] < r) {
                del(news[t][1]);
                add(news[t][0]);
            }
            a[news[t][2]] = news[t][0];
        }
        for (int j = 1; j < MAX; ++j) {
            if (cnt2[j] == 0) {
                ans[qs[i][3]] = j;
                break;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i] != -1) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
