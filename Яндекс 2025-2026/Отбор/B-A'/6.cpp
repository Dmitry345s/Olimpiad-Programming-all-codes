#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")
//#define int long long

using namespace std;

mt19937 rnd(179);

const int MAX = 1e6, INF = 1e9;
int a[MAX];
int now[MAX];
set<pair<int, int>> st0[2];
set<pair<int, int>> st1[2];

int ch(string & s, int n) {
    /*for (int i = 0; i < n; ++i) {
        cout << now[i];
    }
    cout << endl;*/
    st0[0].clear();
    st0[1].clear();
    st1[0].clear();
    st1[1].clear();
    int add0 = 0, add1 = 0, add2 = 0, add3 = 0;
    int l = 0;
    while (l < n) {
        int u = l;
        while (l < n && now[u] == now[l]) {
            l++;
        }
        st0[now[u]].insert({u, l - u});
        st1[now[u]].insert({l - u, u});
    }
    for (int i = 0; i < n - 1; ++i) {
        if ((int)st0[0].size() + (int)st0[1].size() == 1) break;
        //cout << i << endl;
        if (s[i] == 'm') {
            add2 += 1;
            add3 -= 1;
            add1 += 1;
            if (!st0[0].empty()) {
                auto [l1, len1] = *st0[0].begin();
                auto [l2, len2] = *st0[0].rbegin();
                if (l1 + add0 == i) {
                    st0[0].erase({l1, len1});
                    st1[0].erase({len1, l1});
                    st0[0].insert({l1 + 1, len1 - 1});
                    st1[0].insert({len1 - 1, l1 + 1});
                }
                if (l2 + add0 + len2 + add1 - 1 == n) {
                    st0[0].erase({l2, len2});
                    st1[0].erase({len2, l2});
                    st0[0].insert({l2, len2 - 1});
                    st1[0].insert({len2 - 1, l2});
                }
            }
            while (!st1[1].empty() && (*st1[1].begin()).first + add3 == 0) {
                auto [len1, l1] = *st1[1].begin();
                st1[1].erase({len1, l1});
                st0[1].erase({l1, len1});
                auto it = st0[0].upper_bound({l1 + add2 - add0, -1 - add1});
                if (it == st0[0].end() || it == st0[0].begin()) continue;
                auto it2 = it;
                --it2;
                auto [l2, len2] = *it;
                auto [l3, len3] = *it2;
                st0[0].erase({l2, len2});
                st1[0].erase({len2, l2});
                st0[0].erase({l3, len3});
                st1[0].erase({len3, l3});
                int l4 = l3, len4 = len2 + len3 + add1;
                st0[0].insert({l4, len4});
                st1[0].insert({len4, l4});
            }
        } else {
            add0 += 1;
            add1 -= 1;
            add3 += 1;
            if (!st0[1].empty()) {
                auto [l1, len1] = *st0[1].begin();
                auto [l2, len2] = *st0[1].rbegin();
                if (l1 + add2 == i) {
                    st0[1].erase({l1, len1});
                    st1[1].erase({len1, l1});
                    st0[1].insert({l1 + 1, len1 - 1});
                    st1[1].insert({len1 - 1, l1 + 1});
                }
                if (l2 + add2 + len2 + add3 - 1 == n) {
                    st0[1].erase({l2, len2});
                    st1[1].erase({len2, l2});
                    st0[1].insert({l2, len2 - 1});
                    st1[1].insert({len2 - 1, l2});
                }
            }
            while (!st1[0].empty() && (*st1[0].begin()).first + add1 == 0) {
                auto [len1, l1] = *st1[0].begin();
                st1[0].erase({len1, l1});
                st0[0].erase({l1, len1});
                auto it = st0[1].upper_bound({l1 + add0 - add2, -1 - add3});
                if (it == st0[1].end() || it == st0[1].begin()) continue;
                auto it2 = it;
                --it2;
                auto [l2, len2] = *it;
                auto [l3, len3] = *it2;
                st0[1].erase({l2, len2});
                st1[1].erase({len2, l2});
                st0[1].erase({l3, len3});
                st1[1].erase({len3, l3});
                int l4 = l3, len4 = len2 + len3 + add3;
                st0[1].insert({l4, len4});
                st1[1].insert({len4, l4});
            }
        }
        /*for (auto [l1, len1] : st0[0]) {
            cout << l1 + add0 << " " << len1 + add1 << endl;
        }
        cout << "#" << endl;
        for (auto [l1, len1] : st0[1]) {
            cout << l1 + add2 << " " << len1 + add3 << endl;
        }
        cout << endl;*/
    }
    return !st0[1].empty();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int fl = 0;
    int n;
    cin >> n;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    fl = 1;
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    for (int k = 0; k < min(n - 1, 100 * 1ll); ++k) {
        for (int i = 0; i < n - 1; ++i) {
            if (s.back() == 'M') {
                a[i] = max(a[i], a[i + 1]);
            } else {
                a[i] = min(a[i], a[i + 1]);
            }
        }
        s.pop_back();
        n--;
    }
    reverse(s.begin(), s.end());
    while (true) {
        /*int n = rnd() % MAX + 1;
        for (int i = 0; i < n; ++i) {
            a[i] = rnd() % n + 1;
        }
        string s;
        for (int i = 0; i < n - 1; ++i) {
            int t = rnd() % 2;
            if (t) {
                s.push_back('M');
            } else {
                s.push_back('m');
            }
        }*/
        if (n == 1) {
            cout << a[0] << endl;
            if (fl) return 0;
            continue;
        }
        int l = 0, r = (int)b.size();
        while (l + 1 < r) {
            int m = (l + r) / 2;
            for (int i = 0; i < n; ++i) {
                if (a[i] < b[m]) {
                    now[i] = 0;
                } else {
                    now[i] = 1;
                }
            }
            //cout << l << " " << r << endl;
            if (ch(s, n)) {
                l = m;
            } else {
                r = m;
            }
        }
        cout << b[l] << endl;
        /*vector<int> nowb(n);
        for (int i = 0; i < n; ++i) {
            nowb[i] = a[i];
        }
        for (int i = 0; i < n - 1; ++i) {
            vector<int> nxb(n);
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == 'M') {
                    nxb[j] = max(nowb[j - 1], nowb[j]);
                } else {
                    nxb[j] = min(nowb[j - 1], nowb[j]);
                }
            }
            swap(nowb, nxb);
        }
        if (nowb[n - 1] == l) continue;
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
        cout << s << endl;
        cout << l << " " << nowb[n - 1] << endl;*/
        return 0;
    }
    return 0;
}
/*
10
5 10 4 6 6 2 7 3 10 8
MmMMmmMmM
*/
