#include<bits/stdc++.h>

#define int long long

using namespace std;

vector<int> xs, ys;

int ch(int k, vector<array<int, 3>> now, int m) {
    vector<vector<int>> pref((int)xs.size() + 1, vector<int> ((int)ys.size() + 1));
    vector<vector<int>> sr((int)xs.size() + 1, vector<int> ((int)ys.size() + 1));
    for (auto [x, y, s] : now) {
        pref[x][y] += s;
        sr[x][y] += s;
    }
    for (int i = 0; i < (int)xs.size(); ++i) {
        vector<pair<int, int>> st;
        vector<pair<int, int>> st2;
        for (int j = 0; j < (int)ys.size(); ++j) {
            //cout << j << endl;
            if (ys[j] < xs[i]) {
                st.push_back({pref[i][j] - sr[i][j], j});
                st2.push_back({sr[i][j], j});
                continue;
            }
            int del = xs[i];
            if (i != 0) {
                del -= xs[i - 1];
            } else {
                del += 1;
            }
            int del2 = ys[j];
            if (j != 0) {
                del2 -= max(ys[j - 1], xs[i] - 1);
            } else {
                del2 -= xs[i] - 1;
            }
            //cout << del << " " << del2 << endl;
            int need = ((del * (del - 1)) / 2 + del2 * del - del - del2 + 1) * k;
            if (j != 0 && ys[j - 1] >= xs[i]) {
                need = del * del2 * k - del * k - del2 * k + k;
            }
            //cout << "** " << need << endl;
            while (!st.empty() && need > 0) {
                auto [sum, u] = st.back();
                //cout << i << " " << u << " " << sum << endl;
                if (sum <= need) {
                    need -= sum;
                    st.pop_back();
                } else {
                    st.back().first -= need;
                    need = 0;
                }
            }
            if (need > 0) {
                return 0;
            }
            st.push_back({pref[i][j] - sr[i][j], j});
            need = del * k - k;
            while (!st.empty() && need > 0) {
                auto [sum, u] = st.back();
                if (sum <= need) {
                    need -= sum;
                    st.pop_back();
                } else {
                    st.back().first -= need;
                    need = 0;
                }
            }
            if (need > 0) {
                return 0;
            }
            need = del2 * k - k;
            while (!st2.empty() && need > 0) {
                auto [sum, u] = st2.back();
                if (sum <= need) {
                    need -= sum;
                    st2.pop_back();
                } else {
                    st2.back().first -= need;
                    need = 0;
                }
            }
            auto [sum2, u2] = st.back();
            if (u2 == j) st.pop_back();
            while (!st.empty() && need > 0) {
                auto [sum, u] = st.back();
                if (sum <= need) {
                    need -= sum;
                    st.pop_back();
                } else {
                    st.back().first -= need;
                    need = 0;
                }
            }
            if (u2 == j) st.push_back({sum2, u2});
            if (need > 0) {
                return 0;
            }
            st2.push_back({sr[i][j], j});
            need = k;
            while (!st2.empty() && need > 0) {
                auto [sum, u] = st2.back();
                if (sum <= need) {
                    need -= sum;
                    st2.pop_back();
                } else {
                    st2.back().first -= need;
                    need = 0;
                }
            }
            while (!st.empty() && need > 0) {
                auto [sum, u] = st.back();
                if (sum <= need) {
                    need -= sum;
                    st.pop_back();
                } else {
                    st.back().first -= need;
                    need = 0;
                }
            }
            if (need > 0) {
                return 0;
            }
        }
        //cout << i << endl;
        for (auto [sum, u] : st) {
            pref[i + 1][u] += sum;
        }
        for (auto [sum, u] : st2) {
            pref[i + 1][u] += sum;
        }
    }
    return 1;
}

signed main() {
    int m, v;
    cin >> m >> v;
    vector<array<int, 3>> all(v);
    int sum = 0;
    for (int i = 0; i < v; ++i) {
        int x, y, s;
        cin >> x >> y >> s;
        if (x > y) swap(x, y);
        all[i] = {x, y, s};
        xs.push_back(x);
        ys.push_back(y);
        xs.push_back(y);
        ys.push_back(x);
        sum += s;
    }
    /*for (int i = 0; i < m; ++i) {
        xs.push_back(i);
        ys.push_back(i);
    }*/
    xs.push_back(m);
    ys.push_back(m);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < v; ++i) {
        all[i][0] = lower_bound(xs.begin(), xs.end(), all[i][0]) - xs.begin();
        all[i][1] = lower_bound(ys.begin(), ys.end(), all[i][1]) - ys.begin();
    }
    //cout << 0 << endl;
    int l = 0, r = (sum / ((m + 1) * (m + 2) / 2)) + 1;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        //cout << l << " " << r << " " << c << endl;
        if (ch(c, all, m)) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}

