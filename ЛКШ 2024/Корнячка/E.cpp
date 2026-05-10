#include<bits/stdc++.h>

using namespace std;

const int K = 500, MAX = 1e6 + 1;

bool cmp(array<int, 3> a, array<int, 3> b) {
    if (a[0] / K == b[0] / K) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

int cnt [MAX];
long long ans = 0;

void add(int x) {
    ans += (2 * cnt[x] + 1) * x;
    cnt[x]++;
}

void del(int x) {
    ans += (-2 * cnt[x] + 1) * x;
    cnt[x]--;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<array<int, 3>> qs;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        qs.push_back({l, r, i});
    }
    sort(qs.begin(), qs.end(), cmp);
    vector<long long> rans(q);
    int l = 0, r = 0;
    for (int i = 0; i < q; ++i) {
        while (l > qs[i][0]) {
            --l;
            add(a[l]);
        }
        while (r < qs[i][1]) {
            add(a[r]);
            r++;
        }
        while (l < qs[i][0]) {
            del(a[l]);
            ++l;
        }
        while (r > qs[i][1]) {
            r--;
            del(a[r]);
        }
        rans[qs[i][2]] = ans;
    }
    for (int i = 0; i < q; ++i) {
        cout << rans[i] << endl;
    }
    return 0;
}
