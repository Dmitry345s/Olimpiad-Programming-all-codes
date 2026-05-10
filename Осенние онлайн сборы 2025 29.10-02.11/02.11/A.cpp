#include<bits/stdc++.h>
//#include "monster.h"

using namespace std;

vector<int> nowa;

bool Query(int a, int b) {
    if (nowa[a] + 1 == nowa[b] || nowa[a] - 1 > nowa[b]) return 1;
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
    /*vector<int> nnow;
    vector<int> ndo;
    ndo.push_back(now[0]);
    for (int i = 0; i < n - 1; ++i) {
        //ndo.push_back(now[i + 1]);
        if ((int)ndo.size() > 1 && Query(ndo[0], now[i + 1])) {
            reverse(ndo.begin(), ndo.end());
            for (int v : ndo) {
                nnow.push_back(v);
            }
            ndo.clear();
            //cout << i << endl;
        }
        ndo.push_back(now[i + 1]);
    }
    reverse(ndo.begin(), ndo.end());
    for (int v : ndo) {
        nnow.push_back(v);
    }
    now = nnow;*/
int in = 0;
    vector<int> us(n);
    while (in < n) {
        //swap(now[in], now[in + 1]);
        //in++;
        int ch = in;
        while (ch < n && (ch + 2 >= n || Query(now[ch], now[ch + 2]))) {
            ch++;
            //cout << in << " " << ch << endl;
        }
        //cout << in << " " << ch << endl;
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
    nowa.resize(n);
    for (int i = 0; i < n; ++i) {
        nowa[i] = i;
    }
    do {
        vector<int> ans = Solve(n);
        if (ans == nowa) {
            cout << "OK" << endl;
        } else {
            cout << "WA" << endl;
            for (int i = 0; i < n; ++i) {
                cout << nowa[i] << " ";
            }
            cout << endl;
        }
    } while (next_permutation(nowa.begin(), nowa.end()));
}
