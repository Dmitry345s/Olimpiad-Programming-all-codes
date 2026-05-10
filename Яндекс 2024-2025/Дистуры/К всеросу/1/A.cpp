#include<bits/stdc++.h>

using uint = unsigned int;

using namespace std;

const uint C1 = 214013, C2 = 2531011, C1R = 3115528533;

signed main() {
    uint n, a;
    cin >> n >> a;
    vector<pair<int, uint>> st;
    uint ans = 0;
    for (int i = 0; i < n; ++i) {
        while ((int)st.size() > 0 && a >= st.back().second) {
            ans += i - 1;
            st.pop_back();
        }
        if ((int)st.size() != 0) {
            ans -= st.back().first + 1;
        }
        //cout << ans << endl;
        st.push_back({i, a});
        a = (a * C1 + C2);
    }
    cout << ans + (n - 1) * (int)st.size() + n << endl;
    return 0;
}
