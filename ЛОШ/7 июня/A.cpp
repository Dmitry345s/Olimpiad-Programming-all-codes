#include<iostream>
#include<vector>

using namespace std;

int INF = 1e9;

pair<int, int> check(int x, int w, vector<int> a, vector<int> b) {
    int l = x, r = w - x;
    int now = 0;
    int ans1 = 1;
    for (int i = 0; i < int(a.size()); ++i) {
        if (a[i] > l) {
            ans1 = INF;
            break;
        }
        if (now == 0) {
            now = a[i];
        } else if (now + 1 + a[i] > l) {
            ans1 += 1;
            now = a[i];
        } else {
            now += 1 + a[i];
        }
    }
    now = 0;
    int ans2 = 1;
    for (int i = 0; i < int(b.size()); ++i) {
        if (b[i] > r) {
            ans2 = INF;
            break;
        }
        if (now == 0) {
            now = b[i];
        } else if (now + 1 + b[i] > r) {
            ans2 += 1;
            now = b[i];
        } else {
            now += 1 + b[i];
        }
    }
    return {ans1, ans2};
}

int main() {
    int w, n, m;
    cin >> w >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int j = 0; j < m; ++j) {
        cin >> b[j];
    }
    int l = 0, r = w;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        pair<int, int> x = check(m, w, a, b);
        if (x.first > x.second) {
            l = m;
        } else {
            r = m;
        }
    }
    pair<int, int> y1 = check(l, w, a, b), y2 = check(r, w, a, b);
    int x1 = max(y1.first, y1.second), x2 = max(y2.first, y2.second);
    cout << min(x1, x2) << endl;
    return 0;
}
