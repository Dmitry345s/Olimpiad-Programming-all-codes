#include<iostream>
#include<vector>

using namespace std;

int k = 500;
vector<int> a(1e5), b((1e5 + k - 1) / k);

int get_sum(int l, int r) {
    int f = (l + k - 1) / k, s = r / k;
    int f2 = f * k, s2 = s * k;
    int ans = 0;
    if (r < f2) {
        for (int i = l; i < r; ++i) {
            ans += !a[i];
        }
        return ans;
    }
    for (int i = l; i < min(r, f2); ++i) {
        ans += !a[i];
    }
    for (int i = max(l, s2); i < r; ++i) {
        ans += !a[i];
    }
    for (int i = f; i < s; ++i) {
        ans += b[i];
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i / k] += !a[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        cout << get_sum(l - 1, r) << endl;
    }
}
