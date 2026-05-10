#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> ans;

void tr(int now, int n, vector<int> & p, vector<int> & p2) {
    if (now + 4 >= n && now - 3 >= 0) {
        ans.push_back({now + 1, now - 3});
        swap(p2[now + 1], p2[now - 3]);
        p[p2[now + 1]] = now + 1;
        p[p2[now - 3]] = now - 3;
        ans.push_back({now, now - 3});
        swap(p2[now], p2[now - 3]);
        p[p2[now]] = now;
        p[p2[now - 3]] = now - 3;
        ans.push_back({now + 1, now - 3});
        swap(p2[now + 1], p2[now - 3]);
        p[p2[now + 1]] = now + 1;
        p[p2[now - 3]] = now - 3;
    } else if (now + 4 < n) {
        ans.push_back({now, now + 4});
        swap(p2[now], p2[now + 4]);
        p[p2[now]] = now;
        p[p2[now + 4]] = now + 4;
        ans.push_back({now + 1, now + 4});
        swap(p2[now + 1], p2[now + 4]);
        p[p2[now + 1]] = now + 1;
        p[p2[now + 4]] = now + 4;
        ans.push_back({now, now + 4});
        swap(p2[now], p2[now + 4]);
        p[p2[now]] = now;
        p[p2[now + 4]] = now + 4;
    }
}

mt19937 rnd(time(0));

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<pair<int, int>> b;
    vector<int> p(n), p2(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back({a[i], i});
        p[i] = i;
        p2[i] = i;
    }
    sort(b.rbegin(), b.rend());
    if (n <= 6) {
        vector<pair<int, int>> c;
        vector<int> d = a;
        sort(d.rbegin(), d.rend());
        if (a == d) {
            cout << "YES" << endl;
            cout << 0 << endl;
            return 0;
        }
        for (int i = 0; i < n; ++i) {
            if (i + 4 < n) {
                c.push_back({i, i + 4});
            }
            if (i + 3 < n) {
                c.push_back({i, i + 3});
            }
        }
        if (c.size() == 0) {
            cout << "NO" << endl;
            return 0;
        }
        for (int i = 0; i < 1e5; ++i) {
            vector<int> p;
            for (int j = 0; j < 30; ++j) {
                p.push_back(rnd() % c.size());
            }
            vector<int> now = a;
            for (int i = 0; i < p.size(); ++i) {
                swap(now[c[p[i]].first], now[c[p[i]].second]);
                for (int l = 0; l < n; ++l) {
                    //cout << now[l] << " ";
                }
                //cout << endl;
                if (now == d) {
                    cout << "YES" << endl;
                    cout << i + 1 << endl;
                    for (int j = 0; j <= i; ++j) {
                        cout << c[p[j]].first + 1 << " " << c[p[j]].second + 1 << endl;
                    }
                    return 0;
                }
            }
        }
        cout << "NO" << endl;
        return 0;
    }
    if (n <= 8) {
        for (int i = 0; i < n; ++i) {
            int now = p[b[i].second];
            while (now > i) {
                tr(now - 1, n, p, p2);
                now -= 1;
            }
        }
    }
    if (n > 8) {
        for (int i = 0; i < n - 8; ++i) {
            int now = p[b[i].second];
            while (now % 3 != i % 3) {
                if (now + 3 >= n) {
                    now -= 4;
                    ans.push_back({now, now + 4});
                    swap(p2[now], p2[now + 4]);
                    p[p2[now]] = now;
                    p[p2[now + 4]] = now + 4;
                } else {
                    now += 3;
                    ans.push_back({now, now - 3});
                    swap(p2[now], p2[now - 3]);
                    p[p2[now]] = now;
                    p[p2[now - 3]] = now - 3;
                }
            }
            while (now + 3 < n) {
                now += 3;
                ans.push_back({now, now - 3});
                swap(p2[now], p2[now - 3]);
                p[p2[now]] = now;
                p[p2[now - 3]] = now - 3;
            }
            while (now != i) {
                now -= 3;
                ans.push_back({now, now + 3});
                swap(p2[now], p2[now + 3]);
                p[p2[now]] = now;
                p[p2[now + 3]] = now + 3;
            }
        }
        for (int i = n - 8; i < n; ++i) {
            int now = p[b[i].second];
            while (now > i) {
                tr(now - 1, n, p, p2);
                now -= 1;
            }
        }
    }
    cout << "YES" << endl;
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }
    return 0;
    //for (int i = 0; i < n; ++i) {
        //cout << p2[i] << " ";
    //}
    //cout << endl;
            /*vector<pair<int, int>> c;
        vector<int> d = a;
        sort(d.rbegin(), d.rend());
        if (a == d) {
            cout << "YES" << endl;
            cout << 0 << endl;
            return 0;
        }
        for (int i = 0; i < n; ++i) {
            if (i + 4 < n) {
                c.push_back({i, i + 4});
            }
            if (i + 3 < n) {
                c.push_back({i, i + 3});
            }
        }
        vector<int> p(c.size());
        for (int i = 0; i < c.size(); ++i) {
            p[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        do {
            vector<int> now = a;
            for (int i = 0; i < c.size(); ++i) {
                swap(now[c[p[i]].first], now[c[p[i]].second]);
                for (int l = 0; l < n; ++l) {
                    //cout << now[l] << " ";
                }
                //cout << endl;
                if (now == d) {
                    cout << "YES" << endl;
                    cout << i + 1 << endl;
                    for (int j = 0; j <= i; ++j) {
                        cout << c[p[j]].first + 1 << " " << c[p[j]].second + 1 << endl;
                    }
                    return 0;
                }
            }
        } while (next_permutation(p.begin(), p.end()));
        cout << "NO" << endl;
        return 0;*/
}
