#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ans += a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int k;
    cin >> k;
    vector<double> p;
    vector<int> p2;
    for (int i = 0; i < k; ++i) {
        int x;
        double pr;
        cin >> x >> pr;
        if (x == 1) {
            p.push_back(pr / 100);
        } else {
            p2.push_back(pr);
        }
    }
    sort(p.begin(), p.end());
    sort(p2.begin(), p2.end());
    reverse(p2.begin(), p2.end());
    reverse(p.begin(), p.end());
    int i = 0, j = 0, l = 0, r = n - 1;
    while (l <= r && i < p.size() && j < p2.size()) {
        if (p[i] * a[l] < p2[j]) {
            ans += p2[j];
            j += 1;
            r -= 1;
        } else {
            ans += p[i] * a[l];
            l += 1;
            i += 1;
        }
    }
    if (l > r) {
        cout << ans << endl;
        return 0;
    }
    if (i == p.size()) {
        for (int t = j; t < min(j + r - l + 1, int(p2.size())); ++t) {
            ans += p2[t];
        }
    } else {
        for (int t = i; t < min(i + r - l + 1, int(p.size())); ++t) {
            ans += p[t] * a[l];
            ++l;
        }
    }
    cout << ans << endl;
    return 0;
}
