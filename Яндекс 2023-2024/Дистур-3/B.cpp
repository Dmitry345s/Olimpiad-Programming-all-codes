#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, ts;
    cin >> n >> ts;
    vector<int> x(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> t[i];
    }
    multiset<int> st;
    long long sum = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int nt = ts - x[i];
        while (sum > nt && !st.empty()) {
            auto it = st.end();
            --it;
            int k = *it;
            st.erase(it);
            sum -= k;
        }
        if (sum > nt && st.empty()) break;
        if (sum + t[i] <= nt) {
            st.insert(t[i]);
            sum += t[i];
        } else if (!st.empty()) {
            auto it = st.end();
            --it;
            if (*it > t[i]) {
                sum = sum - *it + t[i];
                st.erase(it);
                st.insert(t[i]);
            }
        }
        ans = max(ans, (int)st.size());
    }
    cout << ans << endl;
    return 0;
}
