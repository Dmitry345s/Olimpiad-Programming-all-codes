#include<iostream>
#include<vector>

using namespace std;

int k = 450;

int get_ans(int l, int r, vector<int>& a, vector<int>& b) {
    int n = a.size();
    int s = (l + k - 1) / k, f = r / k;
    int s2 = s * k, f2 = f * k;
    int ans = 1e9;
    for (int i = l; i < min(s2, r); ++i) {
        ans = min(ans, a[i]);
    }
    for (int i = max(f2, l); i < r; ++i) {
        ans = min(ans, a[i]);
    }
    for (int i = s; i < f; ++i) {
        ans = min(ans, b[i]);
    }
    return ans;
}

int main() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    vector<int> b((n + k - 1) / k, 1e9);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i / k] = min(b[i / k], a[i]);
    }
    for (int i = 0; i < n - t + 1; ++i) {
        cout << get_ans(i, i + t, a, b) << " ";
    }
    return 0;
}
