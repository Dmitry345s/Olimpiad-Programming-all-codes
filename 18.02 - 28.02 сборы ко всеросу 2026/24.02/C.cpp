#include<bits/stdc++.h>

using namespace std;


vector<int> str(vector<int> a) {
    int n = (int)a.size();
    vector<int> tol(n);
    for (int i = 0; i < n; ++i) {
        tol[i] = min(n - 1, a[i] + i - 1);
    }
    vector<int> nx(n, n - 1);
    vector<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.back().first <= tol[i]) {
            nx[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({tol[i], i});
    }
    st.clear();
    vector<int> gor(n);
    for (int i = n - 1; i >= 0; --i) {
        gor[i] = i;
        if (nx[i] <= tol[i]) {
            gor[i] = gor[nx[i]];
        }
    }
    return gor;
}

pair<int, int> solve2(vector<int> a, int mx1, int mx2) {
    int n = (int)a.size();
    int ans1 = -1, ans2 = -1;
    for (int i = 0; i <= mx1; ++i) {
        for (int j = mx2; j < n; ++j) {
            swap(a[i], a[j]);
            vector<int> gor = str(a);
            if (gor[0] == n - 1) {
                ans1 = i;
                ans2 = j;
            }
            swap(a[i], a[j]);
        }
    }
    for (int i = 0; i <= mx1; ++i) {
        for (int j = 0; j <= mx1; ++j) {
            swap(a[i], a[j]);
            vector<int> gor = str(a);
            if (gor[0] == n - 1) {
                ans1 = i;
                ans2 = j;
            }
            swap(a[i], a[j]);
        }
    }
    return {ans1, ans2};
}

const int MAX = 5e6 + 1;
int tree[2 * MAX];

void build(int n, vector<int> & a) {
    for (int i = n; i < 2 * n; ++i) {
        tree[i] = a[i - n];
    }
    for (int i = n - 1; i >= 0; --i) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int get(int l, int r, int n) {
    l += n;
    r += n;
    int ans = 0;
    while (l < r) {
        if ((l % 2)) {
            ans = max(ans, tree[l]);
            l += 1;
        }
        l /= 2;
        if (r % 2) {
            ans = max(ans, tree[r - 1]);
        }
        r /= 2;
    }
    return ans;
}

vector<int> prsolve(vector<int> a) {
    int n = (int)a.size();
    vector<int> ans = a;
    vector<int> gor = str(a);
    int mx = 0;
    build(n, gor);
    for (int _ = 0; _ < n; ++_) {
        int ws = a[_];
        int l = 0, r = ws;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            int nmx = max(mx, m + _ - 1);
            int u = get(_ + 1, nmx + 1, n);
            if (u == n - 1) {
                r = m;
            } else {
                l = m;
            }
        }
        ans[_] = r;
        mx = max(mx, a[_] + _ - 1);
        a[_] = ws;
    }
    return ans;
}

const int C = 1000;

pair<int, int> rsolve(vector<int> a, vector<int> b, vector<int> ca, vector<int> cb, int tr) {
    int n = (int)a.size();
    vector<int> nowmx(n + 1);
    for (int i = 0; i < n; ++i) {
        nowmx[i + 1] = a[i] + i - 1;
    }
    for (int i = 1; i < n; ++i) {
        nowmx[i] = max(nowmx[i - 1], nowmx[i]);
    }
    vector<int> gor = str(a);
    build(n, gor);
    for (int i = max(0, n - 1100 - 1); i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int t = max(nowmx[i], i + a[j] - 1);
            int rmx = get(i + 1, t + 1, n);
            if (a[i] > a[j] && j + a[i] - 1 >= tr && (ca[i] <= a[j] || rmx >= j)) {
                return {i, j};
            }
        }
    }
    int m = (int)b.size();
    vector<int> fmx(C + 1);
    for (int i = 0; i < m; ++i) {
        fmx[cb[i]] = max(fmx[cb[i]], b[i]);
    }
    for (int i = 1; i <= C; ++i) {
        fmx[i] = max(fmx[i], fmx[i - 1]);
    }
    vector<int> ch(n);
    for (int i = 0; i < m; ++i) {
        int ri = i + tr;
        int y = max(0, ri - (b[i] - cb[i]));
        if (y < n) {
            ch[y] = max(ch[y], b[i]);
        }
    }
    for (int i = 1; i < n; ++i) {
        ch[i] = max(ch[i], ch[i - 1]);
    }
    for (int i = max(0, n - C - 1); i < n; ++i) {
        if (fmx[a[i]] + i - 1 >= tr) {
            for (int j = 0; j < m; ++j) {
                if (b[j] == fmx[a[i]] && cb[j] <= a[i] && fmx[a[i]] + i - 1 >= tr) {
                    return {i, j + tr};
                }
            }
            //assert(false);
        }
    }
    for (int i = max(0, n - C - 1); i < n; ++i) {
        if (ch[i] + i - 1 >= tr) {
            for (int j = 0; j < m; ++j) {
                int ri = j + tr;
                int y = max(0, ri - (b[j] - cb[j]));
                if (y <= i && b[j] == ch[i] && ch[i] + i - 1 >= tr) {
                    return {i, j + tr};
                }
            }
            //assert(false);
        }
    }
    return {-1, -1};
}

mt19937 rnd(57);

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _ = 1;
    //cin >> _;
    while (_--) {
        int n = rnd() % 50 + 1;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        //for (int i = 0; i < n; ++i) a[i] = rnd() % 5 + 1;
        vector<int> gor = str(a);
        if (gor[0] == n - 1) {
            cout << "OK" << endl;
            continue;
        }
        vector<pair<int, int>> all;
        int nowc = 0;
        while (nowc < n) {
            all.push_back({nowc, gor[nowc]});
            nowc = gor[nowc] + 1;
        }
        vector<int> lf;
        vector<int> rg;
        for (int i = all[0].first; i <= all[0].second; ++i) {
            lf.push_back(a[i]);
        }
        for (int i = all.back().first; i <= all.back().second; ++i) {
            rg.push_back(a[i]);
        }
        vector<int> lf2 = prsolve(lf);
        vector<int> rg2 = prsolve(rg);
        auto [in1, in2] = rsolve(lf, rg, lf2, rg2, all.back().first);
        if (in1 != -1) {
            cout << "SWAP" << endl;
            cout << in1 + 1 << " " << in2 + 1 << endl;
            continue;
        }
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
