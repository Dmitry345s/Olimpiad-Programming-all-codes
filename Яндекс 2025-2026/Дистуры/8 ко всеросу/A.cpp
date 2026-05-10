#include<bits/stdc++.h>

#define int long long

using namespace std;

int solve(vector<vector<int>> a, int n, int m) {
    vector<vector<int>> to_ans(n, vector<int> (m));
    for (int j = 0; j < m; ++j) {
        int ls = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i][j]) ls++;
            if (!a[i][j]) ls = 0;
            to_ans[i][j] = ls;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> left(m, -1);
        vector<int> right(m, m);
        vector<int> st;
        for (int j = 0; j < m; ++j) {
            while (!st.empty() && to_ans[i][st.back()] > to_ans[i][j]) {
                right[st.back()] = j;
                st.pop_back();
            }
            st.push_back(j);
        }
        st.clear();
        for (int j = m - 1; j >= 0; --j) {
            while (!st.empty() && to_ans[i][st.back()] > to_ans[i][j]) {
                left[st.back()] = j;
                st.pop_back();
            }
            st.push_back(j);
        }
        for (int j = 0; j < m; ++j) {
            //cout << right[j] << " " << left[j] << endl;
            ans = max(ans, to_ans[i][j] * (right[j] - left[j] - 1));
        }
    }
    return ans;
}

signed main() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    int yn = n * min(r, 2ll);
    int ym = m * min(c, 2ll);
    vector<vector<int>> a(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    vector<vector<int>> f(yn, vector<int> (ym));
    for (int i = 0; i < yn; ++i) {
        for (int j = 0; j < ym; ++j) {
            f[i][j] = a[i % n][j % m];
        }
    }
    int ans = solve(f, yn, ym);
    vector<vector<int>> ch(yn, vector<int> (1));
    for (int i = 0; i < yn; ++i) {
        int fl = 1;
        for (int j = 0; j < m; ++j) {
            if (!f[i][j]) fl = 0;
        }
        ch[i][0] = fl;
    }
    ans = max(ans, solve(ch, yn, 1) * m * c);
    vector<vector<int>> ch2(1, vector<int> (ym));
    for (int j = 0; j < ym; ++j) {
        int fl = 1;
        for (int i = 0; i < n; ++i) {
            if (!f[i][j]) fl = 0;
        }
        ch2[0][j] = fl;
    }
    ans = max(ans, solve(ch2, 1, ym) * n * r);
    int fl = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!a[i][j]) fl = 0;
        }
    }
    ans = max(ans, n * m * r * c * fl);
    cout << ans << endl;
    return 0;
}
