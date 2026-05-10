#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int t;
    cin >> t;
    int n, h, q;
    cin >> n >> h >> q;
    while (t--) {
        //int maxm = n, in = 0;
        //vector<int> ch2(n);
        vector<pair<int, int>> ch3;
        for (int i = 0; i < n; ++i) {
            cout << "? " << i + 1 << endl;
            int k;
            cin >> k;
            //ch2[i] = k;
            ch3.push_back({k, i});
            //if (k == 1) break;
        }
        sort(ch3.begin(), ch3.end());
        vector<int> vc(h + 1);
        for (int i = 2; i <= h; ++i) {
            vc[i] = vc[i / 2] + 1;
        }
        int x = sqrt(h / 2);
        int ans = 0;
        int l = 0;
        vector<int> u(n);
        int cnt = 0;
        int lp;
        while (h - cnt * x >= x) {
            int p = ch3[0].first;
            if (cnt != 0) {
                cout << "? " << ch3[0].second + 1 << endl;
                cin >> p;
                lp = p;
            }
            for (int i = l; i < p; ++i) {
                u[i] = cnt;
            }
            l = p;
            cout << "- " << ch3[0].second + 1 << " " << x << endl;
            string p2;
            cin >> p2;
            if (p2 == "FAIL") break;
            cnt++;
            ans += x;
        }
        for (int i = l; i < n; ++i) {
            u[i] = cnt;
        }
        int mu = vc[x];
        int st = 0;
        /*for (int j = mu; j >= 0; --j) {
            cout << "- " << ch3[0].second + 1 << " " << (1ll << j) << endl;
            string p2;
            cin >> p2;
            assert(p2 != "-1");
            if (p2 == "FAIL") continue;
            ans += (1ll << j);
            st += (1ll << j);
        }*/
        for (int i = 1; i < n; ++i) {
            if (i >= l) continue;
            cout << "- " << ch3[i].second + 1 << " " << (cnt - u[i]) * x + st << endl;
            string p2;
            cin >> p2;
            assert(p2 != "FAIL");
            ans += (cnt - u[i]) * x + st;
        }
        /*for (int i = 0; i < n; ++i) {
            if (i != ch3[0].second) {
                int mu = vc[x];
                int st = 0;
                for (int j = mu; j >= 0; --j) {
                    cout << "- " << i + 1 << " " << (1ll << j) << endl;
                    string p2;
                    cin >> p2;
                    assert(p2 != "-1");
                    if (p2 == "FAIL") continue;
                    ans += (1ll << j);
                    st += (1ll << j);
                }
            }
        }*/
        ch3.clear();
        int in = ch3[0].second;
        for (int i = 0; i < n; ++i) {
            int k = lp;
            if (i != in) {
                cout << "? " << i + 1 << endl;
                cin >> k;
            }
            assert(k != -1);
            //ch2[i] = k;
            ch3.push_back({k, i});
            //if (k == 1) break;
        }
        sort(ch3.begin(), ch3.end());
        l = 0;
        cnt = 0;
        vector<int> cs;
        while (cnt < 2 * x) {
            int p = ch3[0].first;
            if (cnt != 0) {
                cout << "? " << ch3[0].second + 1 << endl;
                cin >> p;
                lp = p;
            }
            assert(p != -1);
            cs.push_back(p - l);
            l = p;
            cout << "- " << ch3[0].second + 1 << " " << 1 << endl;
            string p2;
            cin >> p2;
            assert(p2 != "-1");
            if (p2 == "FAIL") break;
            cnt++;
        }
        for (int i = 0; i < cs.size(); ++i) {
            ans += cs[i] * (cnt - i);
        }
        cout << "! " << ans << endl;
        string p;
        cin >> p;
        assert(p != "WA");
    }
    return 0;
}
