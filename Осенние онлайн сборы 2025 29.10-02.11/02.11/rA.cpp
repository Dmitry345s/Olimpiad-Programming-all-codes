#include<bits/stdc++.h>
//#include "monster.h"

using namespace std;

bool Query(int a, int b) {
    cout << "? " << a << " " << b << endl;
    int ans;
    cin >> ans;
    if (ans == a) return 1;
    return 0;
}

vector<int> Solve(int n) {
    vector<int> now;
    now.push_back(0);
    for (int i = 1; i < n; ++i) {
        int l = -1, r = (int)now.size();
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (Query(i, now[m])) {
                l = m;
            } else {
                r = m;
            }
        }
        vector<int> an;
        for (int j = 0; j <= l; ++j) {
            an.push_back(now[j]);
        }
        an.push_back(i);
        for (int j = r; j < (int)now.size(); ++j) {
            an.push_back(now[j]);
        }
        now = an;
    }
    //return now;
    int in = 0;
    vector<int> us(n);
    while (in < n) {
        //swap(now[in], now[in + 1]);
        //in++;
        int ch = in;
        cout << in << endl;
        while (ch < n && (ch + 2 >= n || Query(now[ch], now[ch + 2]))) {
            ch++;
            //cout << in << " " << ch << endl;
        }
        cout << in << " " << ch << endl;
        if (ch > in + 1) {
            ch += 2;
            for (int i = in; i < min(ch, n); ++i) {
                us[i] = 1;
            }
            reverse(now.begin() + in, now.begin() + min(ch, n));
            in = ch;
        } else if (ch == in + 1) {
            in = ch + 2;
        } else {
            in = ch + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (us[i] == 1) continue;
        if (us[i] == 0 && (i + 1 >= n || us[i + 1] == 1)) {
            us[i] = 1;
            continue;
        }
        if (us[i] == 0 && us[i + 1] == 0 && (i + 2 >= n || us[i + 2] == 1)) {
            swap(now[i], now[i + 1]);
            us[i] = 1;
            us[i + 1] = 1;
            continue;
        }
        us[i] = 1;
        us[i + 1] = 1;
        us[i + 2] = 1;
        if (i != 0) {
            if (Query(now[i - 1], now[i])) {
                swap(now[i + 1], now[i + 2]);
            } else if (Query(now[i - 1], now[i + 1])) {
                swap(now[i], now[i + 1]);
            } else {
                swap(now[i], now[i + 2]);
            }
        } else {
            if (Query(now[i], now[i + 3])) {
                swap(now[i], now[i + 2]);
            } else if (Query(now[i + 1], now[i + 3])) {
                swap(now[i + 1], now[i + 2]);
            } else {
                swap(now[i], now[i + 1]);
            }
        }
    }
    //return now;
    vector<int> ans(n);
    //reverse(now.begin(), now.end());
    for (int i = 0; i < n; ++i) {
        ans[now[i]] = i;
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> ans = Solve(n);
    cout << "! ";
    for (int v : ans) {
        cout << v << " ";
    }
    cout << endl;
}

