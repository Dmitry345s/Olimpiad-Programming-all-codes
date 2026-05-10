#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int K = 300;

bool cmp(array<int, 3> a, array<int, 3> b) {
    if (a[0] / K == b[0] / K) {
        if ((a[0] / K) % 2 == 0) {
            return a[1] < b[1];
        } else {
            return a[1] > b[1];
        }
    }
    return a[0] / K < b[0] / K;
}

const int MAX = 1e5 + 1;
int cnt[MAX], cnt2[MAX];
int cnt4[MAX];
int cnt3[(MAX + K - 1) / K][MAX];

void add(int x) {
    cnt2[cnt[x]]--;
    cnt3[x / K][cnt[x]]--;
    if (cnt2[cnt[x]] == 0) {
        cnt4[cnt[x] / K]--;
    }
    cnt[x]++;
    if (cnt2[cnt[x]] == 0) {
        cnt4[cnt[x] / K]++;
    }
    cnt2[cnt[x]]++;
    cnt3[x / K][cnt[x]]++;
}

void del(int x) {
    cnt2[cnt[x]]--;
    cnt3[x / K][cnt[x]]--;
    if (cnt2[cnt[x]] == 0) {
        cnt4[cnt[x] / K]--;
    }
    cnt[x]--;
    if (cnt2[cnt[x]] == 0) {
        cnt4[cnt[x] / K]++;
    }
    cnt2[cnt[x]]++;
    cnt3[x / K][cnt[x]]++;
}

signed main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }
    //cout << 0 << endl;
    int q;
    cin >> q;
    vector<array<int, 3>> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i][0] >> qs[i][1];
        --qs[i][0];
        qs[i][2] = i;
    }
    sort(qs.begin(), qs.end(), cmp);
    int l = 0, r = 0;
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        while (r < qs[i][1]) {
            add(a[r]);
            r++;
        }
        while (l > qs[i][0]) {
            l--;
            add(a[l]);
        }
        while (r > qs[i][1]) {
            --r;
            del(a[r]);
        }
        while (l < qs[i][0]) {
            del(a[l]);
            ++l;
        }
        int now = 0;
        for (int j = (MAX + K - 1) / K - 1; j >= 0; --j) {
            if (cnt4[j] != 0) {
                for (int u = min((j + 1) * K, MAX) - 1; u >= j * K; --u) {
                    if (cnt2[u] != 0) {
                        now = u;
                        break;
                    }
                }
                break;
            }
        }
        for (int j = 0; j < (MAX + K - 1) / K; ++j) {
            if (cnt3[j][now] != 0) {
                for (int u = j * K; u < (j + 1) * K; ++u) {
                    if (cnt[u] == now) {
                        ans[qs[i][2]] = u;
                        break;
                    }
                }
                break;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << b[ans[i]] << endl;
    }
    return 0;
}
