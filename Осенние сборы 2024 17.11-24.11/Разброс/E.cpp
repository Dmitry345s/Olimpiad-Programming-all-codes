#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    multiset<int> st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        st.insert(a[i]);
    }
    int ans = 0;
    while ((int)st.size() > 1) {
        int x = (*st.begin());
        st.erase(st.begin());
        int y = (*st.begin());
        st.erase(st.begin());
        ans += x + y;
        st.insert(x + y);
    }
    cout << ans << endl;
    return 0;
}
