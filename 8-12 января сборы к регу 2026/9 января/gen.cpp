#include<bits/stdc++.h>

#define int long long

using namespace std;

mt19937 rnd(69);

const int MOD = 1e9 + 7;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> prefs(m + 1, vector<int>(n + 1));
    prefs[0][0] = 0;
    for (int i = 0; i < n; i++){
        prefs[0][i + 1] = (prefs[0][i] + a[i] * a[i]) % MOD;
    }
    for (int i = 1; i <= m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        l--; r--;
        for (int j = l; j <= r; j++){
            a[j] += x;
            if(a[j] < 0){
                a[j]+= MOD;
            }
            if(a[j] >= MOD){
                a[j] -= MOD;
            }
        }
        prefs[i][0] = 0;
        for (int j = 0; j < n; j++){
            prefs[i][j + 1] = (prefs[i][j] + a[j] * a[j]) % MOD;
        }
    }
    for (int i = 0; i < q; i++){
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--; r--;
        int cnt = 0;
        for (int j = x; j <= y; j++){
            cnt += prefs[j][r + 1] - prefs[j][l] + MOD;
            cnt %= MOD;
        }
        cout << cnt << endl;
    }
}

signed main() {
    solve();
    return 0;
}

/*622394058
147630333
591685461
953957274
929551046
863052007
622899779
662640143
10682333
551945097*/
