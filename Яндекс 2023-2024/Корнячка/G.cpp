#include<bits/stdc++.h>

using namespace std;
using ll = long long;

int k = 350;
vector<array<deque<int>, 2>> b;
vector<ll> sum;

void resum(int i) {
    sum[i] = 0;
    for (int j = 0; j < (int)b[i][0].size(); ++j) {
        sum[i] += b[i][0][j];
    }
    for (int j = 0; j < (int)b[i][1].size(); ++j) {
        sum[i] += b[i][1][j];
    }
}

void update(int l, int r) {
    int l2 = l / k, r2 = r / k;
    if (l2 + 1 >= r2) {
        for (int i = l; i <= r; i += 2) {
            swap(b[i / k][i % 2][i % k / 2], b[(i + 1) / k][(i + 1) % 2][(i + 1) % k / 2]);
        }
        resum(l2);
        resum(r2);
        return;
    }
    for (int i = l; i < (l2 + 1) * k; i += 2) {
        swap(b[i / k][i % 2][i % k / 2], b[(i + 1) / k][(i + 1) % 2][(i + 1) % k / 2]);
    }
    resum(l2);
    for (int i = l2 + 1; i < r2; ++i) {
        if (l % 2 == 1) {
            sum[i] -= b[i - 1][1].back();
            int u = b[i][0].front();
            b[i][0].pop_front();
            sum[i] += u;
            int u2 = b[i][1].back();
            b[i][1].pop_back();
            int u3 = b[i + 1][0].front();
            b[i + 1][0].pop_front();
            swap(b[i][0], b[i][1]);
            b[i][0].push_front(u);
            sum[i] -= u2;
            sum[i] += u3;
            b[i][1].push_back(u3);
            b[i + 1][0].push_front(u2);
        } else {
            swap(b[i][0], b[i][1]);
        }
    }
    for (int i = r2 * k + l % 2; i <= r; i += 2) {
        swap(b[i / k][i % 2][i % k / 2], b[(i + 1) / k][(i + 1) % 2][(i + 1) % k / 2]);
    }
    resum(r2);
}

ll get(int l, int r) {
    int l2 = l / k, r2 = r / k;
    ll ans = 0;
    if (l2 + 1 >= r2) {
        for (int i = l; i <= r; ++i) {
            ans += b[i / k][i % 2][i % k / 2];
        }
        return ans;
    }
    for (int i = l; i < (l2 + 1) * k; ++i) {
        ans += b[i / k][i % 2][i % k / 2];
    }
    for (int i = r2 * k; i <= r; ++i) {
        ans += b[i / k][i % 2][i % k / 2];
    }
    for (int i = l2 + 1; i < r2; ++i) {
        ans += sum[i];
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int ch = 0;
    while (true) {
        ch++;
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) return 0;
        cout << "Swapper " << ch << ":" << endl;
        deque<int> ch2;
        b.assign((n + k - 1) / k, {ch2, ch2});
        sum.assign((n + k - 1) / k, 0);
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            b[i / k][i % 2].push_back(a);
            sum[i / k] += a;
        }
        for (int i = 0; i < m; ++i) {
            int t, l, r;
            cin >> t >> l >> r;
            --l; --r;
            if (t == 1) {
                update(l, r);
            } else {
                cout << get(l, r) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
