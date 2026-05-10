#include<bits/stdc++.h>

using namespace std;

const int K = 320, MAX = 1e5 + 5;
int n;

bool cmp(array<int, 3> a, array<int, 3> b) {
    if (a[0] / K == b[0] / K) {
        return a[1] < b[1];
    }
    return a[0] < b[0];
}

long long tree[MAX];

void add(int in, int x) {
    for (int i = in; i < n + 3; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

long long get(int in) {
    long long ans = 0;
    for (int i = in; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

signed main() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<array<int, 3>> qs;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        qs.push_back({l, r, i});
    }
    sort(qs.begin(), qs.end(), cmp);
    int l = 0, r = 0;
    long long ans = 0;
    vector<long long> rans(q, -1);
    for (int i = 0; i < q; ++i) {
        //cout << qs[i][0] << " " << qs[i][1] << " " << qs[i][2] << endl;
        while (l > qs[i][0]) {
            --l;
            add(a[l], 1);
            ans += get(a[l] - 1);
        }
        while (r < qs[i][1]) {
            ans += get(n + 1) - get(a[r]);
            add(a[r], 1);
            ++r;
        }
        while (l < qs[i][0]) {
            ans -= get(a[l] - 1);
            add(a[l], -1);
            ++l;
        }
        while (r > qs[i][1]) {
            --r;
            add(a[r], -1);
            ans -= get(n + 1) - get(a[r]);
        }
        rans[qs[i][2]] = ans;
    }
    for (int i = 0; i < q; ++i) {
        cout << rans[i] << endl;
    }
    cout << endl;
    return 0;
}
