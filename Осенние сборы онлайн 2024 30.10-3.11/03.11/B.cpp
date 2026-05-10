#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, n;
    cin >> m >> n;
    vector<array<int, 3>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i][0] >> all[i][1];
        all[i][2] = i;
    }
    sort(all.rbegin(), all.rend());
    int toch = 0;
    for (int i = 0; i < n; ++i) {
        toch += all[i][1];
        swap(all[i][1], all[i][0]);
        if (toch >= 6 * m) {
            all[i][0] -= (toch - 6 * m);
            for (int j = i + 1; j < n; ++j) all.pop_back();
            break;
        }
    }
    n = (int)all.size();
    sort(all.rbegin(), all.rend());
    for (int i = 0; i < n; ++i) {
        swap(all[i][0], all[i][1]);
    }
    int now = 0;
    vector<int> st(6, -1);
    vector<array<int, 3>> ans;
    vector<int> rst(6);
    long long z = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        //cout << cnt << " " << now << " " << all[i][0] << " " << all[i][1] << " " << all[i][2] << endl;
        if (now + all[i][1] < m) {
            //cout << i << endl;
            ans.push_back({now, st[cnt], all[i][2]});
            if (st[cnt] == -1) {
                rst[cnt] = all[i][2];
            }
            st[cnt] = all[i][2];
            z += 1ll * all[i][1] * all[i][0];
            now += all[i][1];
        } else if (now + all[i][1] == m) {
            //cout << "! " << i << endl;
            ans.push_back({now, st[cnt], all[i][2]});
            if (st[cnt] == -1) {
                rst[cnt] = all[i][2];
            }
            st[cnt] = all[i][2];
            z += 1ll * all[i][1] * all[i][0];
            now = 0;
            cnt++;
            if (cnt == 6) break;
        } else {
            //cout << "? " << i << endl;
            ans.push_back({now, st[cnt], all[i][2]});
            if (st[cnt] == -1) {
                rst[cnt] = all[i][2];
            }
            st[cnt] = all[i][2];
            z += 1ll * (m - now) * all[i][0];
            cnt++;
            if (cnt == 6) break;
            ans.push_back({0, st[cnt], all[i][2]});
            if (st[cnt] == -1) {
                rst[cnt] = all[i][2];
            }
            st[cnt] = all[i][2];
            now = -(m - now - all[i][1]);
            z += 1ll * now * all[i][0];
        }
    }
    //sort(ans.begin(), ans.end());
    cout << z << '\n';
    for (int i = 0; i < 6; ++i) {
        cout << rst[i] + 1 << " ";
    }
    cout << '\n';
    cout << (int)ans.size() - 6 << '\n';
    for (auto [t, i, j] : ans) {
        if (i == -1) continue;
        cout << t << " " << i + 1 << " " << j + 1 << '\n';
    }
    return 0;
}

