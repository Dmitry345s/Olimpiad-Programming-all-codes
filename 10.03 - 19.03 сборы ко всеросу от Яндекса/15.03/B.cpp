#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> f(n, vector<int> (n, -1));
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            char c;
            cin >> c;
            int u = (c == 'R');
            f[i][j] = u;
            f[j][i] = u;
        }
    }
    int x;
    cin >> x;
    vector<vector<int>> ans(n);
    for (int i = 0; i < n; ++i) {
        int st = i;
        deque<int> left;
        deque<int> right;
        int ll = -1, rr = -1;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            if (left.empty() && right.empty()) {
                left.push_back(st);
                ll = f[st][j];
                st = j;
                continue;
            }
            if (left.empty()) {
                right.push_front(st);
                st = right.back();
                right.pop_back();
                swap(left, right);
                ll = rr;
            }
            if (right.empty()) {
                if (f[st][j] == ll) {
                    left.push_back(st);
                    st = j;
                } else {
                    right.push_front(j);
                    rr = f[st][j];
                }
                continue;
            }
            if (f[st][j] == ll) {
                int v = right.front();
                if (f[v][j] == ll) {
                    right.pop_front();
                    left.push_back(st);
                    left.push_back(j);
                    st = v;
                } else {
                    left.push_back(st);
                    st = j;
                }
            } else {
                int v = left.back();
                if (f[j][v] == rr) {
                    left.pop_back();
                    right.push_front(st);
                    right.push_front(j);
                    st = v;
                } else {
                    right.push_front(st);
                    st = j;
                }
            }
        }
        for (auto x : left) {
            ans[i].push_back(x);
        }
        ans[i].push_back(st);
        for (auto x : right) {
            ans[i].push_back(x);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << n << endl;
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] + 1 << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
