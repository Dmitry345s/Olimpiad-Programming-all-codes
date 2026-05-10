#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e6 + 1, p = 179, MOD = 1e9 + 7;
int pows[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k, q;
    cin >> n >> k >> q;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i] - '0';
    }
    vector<int> next(n, n + 1);
    int rt = n + 1;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == 1) rt = i;
        next[i] = rt;
    }
    int u = fpow(p, MOD - 2);
    vector<int> pref2(n + 1);
    pref2[0] = 0;
    pows[0] = 1;
    for (int i = 0; i < n; ++i) {
        pref2[i + 1] = pref2[i] + a[i];
        pows[i + 1] = (pows[i] * p) % MOD;
    }
    vector<int> last = {-n};
    vector<int> pref(n + 1, -1);
    vector<int> pref3(n + 1, 0);
    vector<int> pref4(n + 1, 0);
    vector<int> pref5(n + 1, 0);
    deque<int> dq;
    int nowh = 0;
    pref[0] = 0;
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
        int c = a[j];
        int t = upper_bound(last.begin(), last.end(), j - k) - last.begin();
        if ((int)dq.size() > 0 && dq.front() <= j - k + 1) {
            nowh = (nowh - pows[k - 1] + MOD) % MOD;
            dq.pop_front();
        }
        //cout << nowh << endl;
        c = (c ^ ((int)dq.size() % 2));
        if (dq.empty() && c == 0) {
            pref[j + 1] = cnt;
        } else {
            //cout << j << " " << (int)dq.size() << endl;
            if (c == 1) {
                cnt++;
                dq.push_back(j);
                nowh = (nowh + 1) % MOD;
            }
            pref5[j + 1] = (int)dq.size();
        }
        pref3[j + 1] = cnt;
        pref4[j + 1] = nowh;
        nowh = (nowh * p) % MOD;
        cout << nowh << endl;
    }
    //cout << endl;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        if (next[l] >= r) {
            cout << 0 << endl;
            continue;
        }
        l = next[l];
        if (k == 0 || r - l < k) {
            if (pref2[r] - pref2[l] != 0) {
                cout << -1 << endl;
            } else {
                cout << 0 << endl;
            }
            continue;
        }
        if (pref4[l] == pref4[r] && pref5[r] == pref5[l]) {
            cout << pref3[r] - pref3[l] << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
