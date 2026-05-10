#include<iostream>
#include<vector>

using namespace std;

int bl = 500;

int get_max(int l, int r, vector<int> & a, vector<pair<int, int>> & b) {
    int f = (l + bl - 1) / bl, s = r / bl;
    int f2 = f * bl, s2 = s * bl;
    int ans = 0;
    for (int i = l; i < min(f2, r); ++i) {
        ans = max(ans, a[i] + b[max(0, f - 1)].second);
    }
    for (int i = max(s2, l); i < r; ++i) {
        ans = max(ans, a[i] + b[s].second);
    }
    for (int i = f; i < s; ++i) {
        ans = max(ans, b[i].first + b[i].second);
    }
    return ans;
}

void update(int l, int r, vector<int> & a, vector<pair<int, int>> & b) {
    int f = (l + bl - 1) / bl, s = r / bl;
    int f2 = f * bl, s2 = s * bl;
    if (r < f2) {
        for (int i = l; i < r; ++i) {
            a[i] += 1;
            b[i / bl].first = max(a[i], b[i / bl].first);
        }
        return;
    }
    for (int i = l; i < min(f2, r); ++i) {
        a[i] += 1;
        b[i / bl].first = max(a[i], b[i / bl].first);
    }
    for (int i = max(s2, l); i < r; ++i) {
        a[i] += 1;
        b[i / bl].first = max(a[i], b[i / bl].first);
    }
    for (int i = f; i < s; ++i) {
        b[i].second += 1;
    }
}

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<int> a(n + 1);
    vector<pair<int, int>> b((n + bl) / bl);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        int maxm = get_max(l, r, a, b);
        if (maxm < k) {
            cout << 1 << endl;
            update(l, r, a, b);
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}
