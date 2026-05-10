#include<bits/stdc++.h>

#pragma GCC optmize("O3")
#pragma GCC optmize("unroll-loops")

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> p(n);
        vector<int> tr(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            p[i]--;
            tr[i] = i;
        }
        sort(p.begin(), p.end());
        vector<int> p3(n);
        for (int i = 0; i < n; ++i) {
            p3[i] = (p[i] + i) % n;
        }
        sort(p3.begin(), p3.end());
        p3.erase(unique(p3.begin(), p3.end()), p3.end());
        if ((int)p3.size() != n) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        for (int i = 0; i < n; ++i) {
            cout << p[i] + 1 << " ";
        }
        cout << endl;
        continue;
        int fl = 0;
        vector<int> ans(n, -1);
        do {
            vector<int> p2(n);
            int flg = 1;
            for (int i = 0; i < n; ++i) {
                int x = (p[i] + tr[i]) % n;
                p2[x]++;
                if (p2[x] == 2) {
                    flg = 0;
                    break;
                }
            }
            if (flg) {
                fl = 1;
                ans = tr;
                break;
            }
        } while (next_permutation(tr.begin(), tr.end()));
        if (!fl) {
            cout << "NO" << '\n';
            continue;
        }
        cout << "YES" << '\n';
        vector<int> rans(n);
        for (int i = 0; i < n; ++i) {
            rans[ans[i]] = p[i] + 1;
        }
        for (int i = 0; i < n; ++i) {
            cout << rans[i] << " ";
        }
        cout << '\n';
    }
    return 0;
}
