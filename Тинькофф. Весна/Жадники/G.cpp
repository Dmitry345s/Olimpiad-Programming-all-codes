#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long ans = 0;

void haha(long long m, vector<long long>& a) {
    if (m <= 0) {
        return;
    }
    vector<pair<double, vector<long long>>> p;
    long long x = 1;
    for (int i = 0; i < 31; ++i) {
        if (a[i] == 0) {
            x *= 2;
            continue;
        }
        if (m < a[i]) {
            double y = x;
            p.push_back({m / y, {a[i], x, 1}});
        } else {
            double y = x;
            p.push_back({a[i] / y, {a[i], x, m / a[i]}});
        }
        x *= 2;
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
    ans += p[0].second[1] * p[0].second[2];
    m -= p[0].second[0] * p[0].second[2];
    haha(m, a);
}

int main() {
    long long m;
    cin >> m;
    vector<long long> a(31);
    for (int i = 0; i < 31; ++i) {
        cin >> a[i];
    }
    haha(m, a);
    cout << ans << endl;
    return 0;
}
