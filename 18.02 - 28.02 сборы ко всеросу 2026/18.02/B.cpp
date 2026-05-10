#include<bits/stdc++.h>

using namespace std;

vector<int> ans;

void solve(vector<int> a, int ndeep) {
    int n = (int)a.size();
    if (n == 1) return;
    for (int i = 0; i < n / 2; ++i) {
        int x1 = 2 * i;
        int x2 = 2 * i + 1;
        while (a[0] != x1 && a[0] != x2) {
            for (int _ = 0; _ < ndeep; ++_) {
                ans.push_back(n * ndeep);
            }
            a.insert(a.begin(), a.back());
            a.pop_back();
        }
        while (a[1] != x1 && a[1] != x2) {
            for (int _ = 0; _ < ndeep; ++_) {
                ans.push_back(n * ndeep);
            }
            a.insert(a.begin(), a.back());
            a.pop_back();
            if (a[0] == x1 && a[1] == x2 || a[0] == x2 && a[1] == x1) break;
            for (int _ = 0; _ < ndeep; ++_) {
                ans.push_back(2 * ndeep);
            }
            swap(a[0], a[1]);
        }
        if (a[0] > a[1]) {
            for (int _ = 0; _ < ndeep; ++_) {
                ans.push_back(2 * ndeep);
            }
            swap(a[0], a[1]);
        }
    }
    vector<int> na;
    for (int i = 0; i < n; i += 2) {
        na.push_back(a[i] / 2);
    }
    solve(na, ndeep * 2);
}

signed main() {
    int n, g;
    cin >> n >> g;
    vector<int> a(n);
    vector<pair<int, int>> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(b.begin(), b.end(), pair<int, int> {a[i], i}) - b.begin();
    }
    solve(a, 1);
    assert((int)ans.size() <= 16384 + 3);
    cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
