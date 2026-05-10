#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 5e5 + 1;
int a[MAX];
const int MOD = 1e9 + 7;
int ans = 0;

void get(vector<int> a){
    if(a.size() == 1){
        ans += a[0] * a[0];
        ans %= MOD;
        return;
    }
    vector<int> r1, r2;
    int m = a.size() / 2;
    for(int i = 0; i < m; i++){
        r1.push_back(a[i]);
    }
    for(int i = m; i < a.size(); i++){
        r2.push_back(a[i]);
    }
    get(r1); get(r2);
    vector<int> prefmnmx(r2.size() + 1), prefmn(r2.size() + 1), prefmx(r2.size() + 1);
    int mn = 1e9, mx = -1e9;
    for(int i = 0; i < r2.size(); i++){
        mn = min(mn, r2[i]);
        mx = max(mx, r2[i]);
        prefmnmx[i + 1] = (prefmnmx[i] + mn * mx) % MOD;
        prefmnmx[i + 1] %= MOD;
        prefmx[i + 1] = (prefmx[i] + mx) % MOD;
        prefmn[i + 1] = (prefmn[i] + mn) % MOD;
    }
    int fminn = -1, fmaxx = -1;
    mn = 1e9, mx = -1e9;
    for(int i = m - 1; i >= 0; i--){
        mx = max(mx, r1[i]);
        mn = min(mn, r1[i]);
        while(fminn + 1 < r2.size() && r2[fminn + 1] >= mn){
            fminn++;
        }
        while(fmaxx + 1 < r2.size() && r2[fmaxx + 1] <= mx){
            fmaxx++;
        }
        if(fminn < fmaxx){
            ans += (fminn + 1) * (mn * mx) % MOD;
            ans %= MOD;
            ans += mx * (prefmn[fmaxx + 1] - prefmn[fminn + 1] + MOD) % MOD;
            ans %= MOD;
            ans += (prefmnmx[r2.size()] - prefmnmx[fmaxx + 1] + MOD) % MOD;
            ans %= MOD;
        }else{
            ans += (fmaxx + 1) * (mn * mx) % MOD;
            ans %= MOD;
            ans += mn * (prefmx[fminn + 1] - prefmx[fmaxx + 1] + MOD) % MOD;
            ans %= MOD;
            ans += (prefmnmx[r2.size()] - prefmnmx[fminn + 1] + MOD) % MOD;
            ans %= MOD;
        }
    }
}


int solve1(vector<int> prefmn, vector<int> prefmx, vector<int> sufmn, vector<int> sufmx) {
    int l1 = 0;
    int l2 = 0;
    int sum1 = 0;
    int sum2 = 0;
    int ans = 0;
    for (int i = 0; i < (int)sufmn.size(); ++i) {
        while (l1 < (int)prefmn.size() && prefmn[l1] >= sufmn[i]) {
            sum1 += prefmx[l1];
            l1++;
        }
        while (l2 < (int)prefmx.size() && prefmx[l2] <= sufmx[i]) {
            sum2 += prefmx[l2];
            l2++;
        }
        if (l2 <= l1) {
            ans = (ans + sufmn[i] * (sum1 - sum2)) % MOD;
        }
    }
    return ans;
}

int solve2(vector<int> prefmn, vector<int> prefmx, vector<int> sufmn, vector<int> sufmx) {
    int l1 = 0;
    int ans = 0;
    for (int i = 0; i < (int)sufmn.size(); ++i) {
        while (l1 < (int)prefmn.size() && prefmn[l1] > sufmn[i] && prefmx[l1] <= sufmx[i]) {
            l1++;
        }
        ans = (ans + sufmn[i] * sufmx[i] % MOD * l1) % MOD;
    }
    return ans;
}

int inter(int l1, int r1, int l2, int r2) {
    return max(0ll, min(r1, r2) - max(l1, l2));
}

int solve4(vector<int> prefmn, vector<int> prefmx, vector<int> sufmn, vector<int> sufmx) {
    int l1 = 0;
    int l2 = 0;
    int l3 = 0;
    int l4 = 0;
    int ans = 0;
    for (int i = 0; i < (int)sufmn.size(); ++i) {
        while (l1 < (int)prefmn.size() && prefmn[l1] > sufmn[i]) {
            l1++;
        }
        while (l3 < (int)prefmx.size() && prefmx[l3] < sufmx[i]) {
            l3++;
        }
        while (l2 < (int)prefmn.size() && prefmn[l2] >= sufmn[i]) {
            l2++;
        }
        while (l4 < (int)prefmx.size() && prefmx[l4] <= sufmx[i]) {
            l4++;
        }
        //cout << i << " " << l1 << " " << l2 << " " << l3 << " " << l4 << endl;
        ans = (ans + sufmn[i] * sufmx[i] % MOD * inter(l1, l2, l3, l4)) % MOD;
    }
    return ans;
}

int solve(int l, int r) {
    if (l + 1 == r) {
        return (a[l] * a[l]) % MOD;
    }
    int m = (l + r) / 2;
    int ans = (solve(l, m) + solve(m, r)) % MOD;
    vector<int> prefmn;
    vector<int> prefmx;
    prefmn.push_back(a[m]);
    prefmx.push_back(a[m]);
    for (int i = m + 1; i < r; ++i) {
        prefmn.push_back(min(prefmn.back(), a[i]));
        prefmx.push_back(max(prefmx.back(), a[i]));
    }
    vector<int> sufmn;
    vector<int> sufmx;
    sufmn.push_back(a[m - 1]);
    sufmx.push_back(a[m - 1]);
    for (int i = m - 2; i >= l; --i) {
        sufmn.push_back(min(sufmn.back(), a[i]));
        sufmx.push_back(max(sufmx.back(), a[i]));
    }
    /*cout << solve1(prefmn, prefmx, sufmn, sufmx) << endl;
    cout << solve2(prefmn, prefmx, sufmn, sufmx) << endl;
    cout << solve1(sufmn, sufmx, prefmn, prefmx) << endl;
    cout << solve2(sufmn, sufmx, prefmn, prefmx) << endl;
    cout << solve4(prefmn, prefmx, sufmn, sufmx) << endl;*/

    ans = (ans + solve1(prefmn, prefmx, sufmn, sufmx)) % MOD;
    ans = (ans + solve2(prefmn, prefmx, sufmn, sufmx)) % MOD;
    ans = (ans + solve1(sufmn, sufmx, prefmn, prefmx)) % MOD;
    ans = (ans + solve2(sufmn, sufmx, prefmn, prefmx)) % MOD;
    ans = (ans + solve4(prefmn, prefmx, sufmn, sufmx) + MOD) % MOD;
    //cout << l << " " << r << " " << ans << endl;
    return ans;
}

int solve0(int n) {
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        int nowmn = a[l];
        int nowmx = a[l];
        for (int r = l; r < n; ++r) {
            ans += nowmn * nowmx;
            ans %= MOD;
            nowmn = min(a[r + 1], nowmn);
            nowmx = max(a[r + 1], nowmx);
        }
    }
    return ans;
}

mt19937 rnd(time(0));

void gen() {
    int n = rnd() % 3 + 1;
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        a[i] = rnd() % MOD;
        b.push_back(a[i]);
    }
    ans = 0;
    get(b);
    int ans2 = solve(0, n);
    if (ans != ans2) {
        cout << "WA" << endl;
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
        cout << ans2 << endl;
        exit(0);
    }
    cout << "OK" << endl;
}


signed main() {
    /*int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << solve(0, n) << endl;*/
    //cout << solve0(n) <<endl;
    int _;
    cin >> _;
    while (_--) {
        gen();
    }
    return 0;
}
