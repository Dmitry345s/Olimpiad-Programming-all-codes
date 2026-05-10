#include<bits/stdc++.h>

#define int long long

using namespace std;

struct D {
    int a, b;
    D(int a1 = 0, int b1 = 1) {
        int x = __gcd(a1, b1);
        a = a1 / x;
        b = b1 / x;
    }
};

bool operator< (D a, D b) {
    return a.a * b.b < b.a * a.b;
}

bool operator== (D a, D b) {
    return a.a * b.b == b.a * a.b;
}

bool operator<= (D a, D b) {
    return a < b || a == b;
}

D find(vector<pair<int, int>> & st, vector<D> & st2, pair<int, int> to) {
    int n = (int)st.size();
    int l = -1, r = n - 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (st[m].second < to.second) {
            r = m;
            continue;
        }
        D now = D(st[m].first - to.first, st[m].second - to.second);
        if (now <= st2[m]) {
            l = m;
        } else {
            r = m;
        }
    }
    return D(st[r].first - to.first, st[r].second - to.second);
}

D find2(vector<pair<int, int>> & st, vector<D> & st2, pair<int, int> to) {
    int n = (int)st.size();
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (st[m].second > to.second) {
            r = m;
            continue;
        }
        D now = D(to.first - st[m].first, to.second - st[m].second);
        if (now <= st2[m - 1]) {
            l = m;
        } else {
            r = m;
        }
    }
    return D(to.first - st[l].first, to.second - st[l].second);
}

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first;
        all[i].second = i + 1;
    }
    sort(all.begin(), all.end());
    vector<int> whr(n + 1);
    for (int i = 0; i < n; ++i) {
        whr[all[i].second] = i;
    }
    vector<int> qs(n);
    for (int i = 0; i < n; ++i) {
        int q;
        cin >> q;
        qs[whr[i + 1]] = whr[q];
    }
    vector<pair<int, int>> st;
    vector<D> st2;
    vector<D> ans(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        while ((int)st.size() > 0 && st.back().second <= all[i].second) {
            st.pop_back();
            if ((int)st2.size() > 0) {
                st2.pop_back();
            }
        }
        while ((int)st2.size() > 0 && st2.back() <= D(st.back().first - all[i].first, st.back().second - all[i].second)) {
            st2.pop_back();
            st.pop_back();
        }
        if ((int)st.size() > 0) {
            st2.push_back(D(st.back().first - all[i].first, st.back().second - all[i].second));
        }
        st.push_back({all[i].first, all[i].second});
        if (qs[i] < i) {
            if (st[0].second > all[qs[i]].second) {
                ans[all[i].second] = find(st, st2, all[qs[i]]);
            } else {
                ans[all[i].second] = D(-1, 1);
            }
        }
    }
    st.clear();
    st2.clear();
    for (int i = 0; i < n; ++i) {
        while ((int)st.size() > 0 && all[i].second <= st.back().second) {
            st.pop_back();
            if ((int)st2.size() > 0) {
                st2.pop_back();
            }
        }
        while ((int)st2.size() > 0 && st2.back() <= D(all[i].first - st.back().first, all[i].second - st.back().second)) {
            st2.pop_back();
            st.pop_back();
        }
        if ((int)st.size() > 0) {
            st2.push_back(D(all[i].first - st.back().first, all[i].second - st.back().second));
        }
        st.push_back({all[i].first, all[i].second});
        if (qs[i] > i) {
            if (st[0].second <= all[qs[i]].second) {
                ans[all[i].second] = find2(st, st2, all[qs[i]]);
            } else {
                ans[all[i].second] = D(-1, 1);
            }
        }
    }
    //cout << __gcd((1ll << 32), (1ll << 33)) << endl;
    for (int i = 1; i <= n; ++i) {
        if (ans[i].a == -1) {
            cout << -1 << endl;
        } else {
            cout << ans[i].a << "/" << ans[i].b << endl;
        }
    }
    return 0;
}
