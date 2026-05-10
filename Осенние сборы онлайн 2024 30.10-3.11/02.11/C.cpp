#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());
    for (int i = 0; i < n; ++i) {
        a.push_back(0);
    }
    vector<int> suf(n + 1);
    suf[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = suf[i + 1] + a[i];
    }
    for(int i = 0; i < n; ++i) {
        suf.push_back(0);
    }
    int now = 2e18;
    int tan1 = -1, tan2 = -1;
    for (int q = 1; q <= n; ++q) {
        int m = n;
        if (n % q != 0) {
            m += (q - n % q);
        }
        //cout << q << " " << m << endl;
        int l = 0, r = q + 1;
        while (l + 1 < r) {
            int c = (l + r) / 2;
            int x = c;
            int sum1 = 0, sum2 = suf[0] - suf[c];
            x += q;
            while (x <= m) {
                if (((x - c) / q) % 2 == 1) {
                    sum1 += suf[x - q] - suf[x];
                } else {
                    sum2 += suf[x - q] - suf[x];
                }
                x += q;
            }
            //cout << c << " " << sum1 << " " << sum2 << endl;
            if (((x - c) / q) % 2 == 1) {
                sum1 += suf[x - q];
            } else {
                sum2 += suf[x - q];
            }
            if ((sum2 > sum1 || c == q) && c != 1) {
                r = c;
            } else {
                l = c;
            }
            //cout << c << " " << sum1 << " " << sum2 << endl;
            if (abs(sum1 - sum2) < now) {
                now = abs(sum1 - sum2);
                tan1 = c;
                tan2 = q;
            }
        }
    }
    cout << tan1 << " " << tan2 << endl;
    return 0;
}
