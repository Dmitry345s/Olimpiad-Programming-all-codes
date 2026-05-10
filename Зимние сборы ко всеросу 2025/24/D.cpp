#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

signed main() {
    int _;
    cin >> _;
    int n, K;
    cin >> n >> K;
    vector<array<int, 4>> all(n);
    for (int i = 0; i < n; ++i) {
        int d, a, b;
        cin >> d >> a >> b;
        all[i] = {d, a, b, i};
    }
    //sort(all.begin(), all.end());
    vector<int> ans((1 << n), -INF);
    for (int i = 0; i < (1 << n); ++i) {
        vector<array<int, 4>> now;
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                now.push_back(all[j]);
                sum -= all[j][2];
            }
        }
        //cout << "# " << i << " " << sum << endl;
        sort(now.begin(), now.end());
        ans[i] = sum;
        for (int k = 0; k < (1 << (int)now.size()); ++k) {
            int fl = 1;
            int last = 0;
            int nsum = sum;
            for (int j = 0; j < (int)now.size(); ++j) {
                if ((k >> j) & 1) {
                    if (last + K > now[j][0]) {
                        fl = 0;
                    }
                    last += K;
                    nsum += now[j][1] + now[j][2];
                }
            }
            //cout << k << " " << fl << " " << nsum << endl;
            if (fl) {
                ans[i] = max(ans[i], nsum);
            }
        }
    }
    int rans = 0;
    int mask = 0;
    for (int i = 0; i < (1 << n); ++i) {
        if (ans[i] < rans) {
            rans = ans[i];
            mask = i;
        }
    }
    cout << rans << endl;
    for (int i = 0; i < n; ++i) {
        cout << ((mask >> i) & 1) << " ";
    }
    cout << endl;
    return 0;
}
