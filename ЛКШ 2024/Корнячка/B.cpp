#include<bits/stdc++.h>

using namespace std;

const int K = 500;

vector<long long> upd(vector<long long> a, vector<array<long long, 4>> qs) {
    vector<long long> ans = a;
    vector<long long> add1((int)a.size() + 1);
    vector<long long> add2((int)a.size() + 1);
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        add1[i + 1] = a[i + 1] - a[i];
        //cout << add1[i + 1] << " ";
    }
    //cout << endl;
    for (int i = 1; i < (int)a.size() - 1; ++i) {
        add2[i + 1] = add1[i + 1] - add1[i];
        //cout << add2[i + 1] << " ";
    }
    //cout << endl;
    for (auto [l, r, x, y] : qs) {
        //add1[l] += x;
        //add1[r + 1] -= x + (r - l) * y;
        add2[l + 1] += y;
        add2[r + 1] -= y;
    }
    add1[1] += add2[1];
    for (int i = 2; i < (int)a.size(); ++i) {
        add1[i] = add1[i - 1] + add2[i];
        //cout << add1[i] << endl;
    }
    //cout << endl;
    for (auto [l, r, x, y] : qs) {
        add1[l] += x;
        add1[r + 1] -= x + (r - l) * y;
        //add2[l + 1] += y;
        //add2[r + 1] -= y;
    }
    ans[0] += add1[0];
    for (int i = 1; i < (int)a.size(); ++i) {
        ans[i] = ans[i - 1] + add1[i];
        //cout << ans[i] << " ";
    }
    //cout << endl;
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    int q;
    cin >> q;
    vector<array<long long, 4>> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2] >> qs[i][3];
        --qs[i][0]; --qs[i][1];
    }
    vector<long long> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        if (a[i] >= b[i]) ans[i] = 0;
    }
    for (int i = 0; i < (q + K - 1) / K; ++i) {
        vector<array<long long, 4>> qs2;
        for (int j = i * K; j < min(q, (i + 1) * K); ++j) {
            qs2.push_back(qs[j]);
        }
        vector<long long> c = upd(a, qs2);
        for (int k = 0; k < n; ++k) {
            if (c[k] >= b[k] && ans[k] == -1) {
                long long now = a[k];
                if (now >= b[k]) {
                    ans[k] = i * K;
                    break;
                }
                for (int j = i * K; j < min(q, (i + 1) * K); ++j) {
                    if (qs[j][0] <= k && k <= qs[j][1]) {
                        now += qs[j][2] + (k - qs[j][0]) * qs[j][3];
                    }
                    if (now >= b[k]) {
                        ans[k] = j + 1;
                        break;
                    }
                }
            }
        }
        a = c;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
