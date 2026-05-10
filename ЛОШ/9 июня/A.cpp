#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    vector<int> b(n);
    int i = 1;
    while (i < n && a[i].first == a[0].first) {
        ++i;
    }
    int p, u, h;
    if (i <= k) {
        p = m - (k - i);
        u = p / i;
        h = p % i;
    } else {
        u = m / i;
        h = m % i;
    }
    for (int l = 0; l < max(i, k); ++l) {
        if (l < h) {
            b[a[l].second] += 1 + u;
        } else if (l < i) {
            b[a[l].second] += u;
        } else {
            b[a[l].second] += 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int l = 0; l < b[i]; ++l) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    return 0;
}
