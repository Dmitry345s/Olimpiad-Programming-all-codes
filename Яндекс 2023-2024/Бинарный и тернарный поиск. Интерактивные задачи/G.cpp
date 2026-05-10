#include<bits/stdc++.h>

using namespace std;

void ask(int r, set<int> & st, long long & s, int & l) {
    l = *(st.begin());
    int lb, rb;
    cout << "? " << l << " " << r << endl;
    cin >> s >> lb >> rb;
    st.erase(lb);
}

signed main() {
    int n;
    cin >> n;
    set<int> st;
    for (int i = 1; i <= n; ++i) {
        st.insert(i);
    }
    vector<int> a(n + 1);
    vector<long long> pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; ++i) {
        long long s;
        int l;
        ask(i, st, s, l);
        long long s2 = pref[i - 1] - pref[l - 1];
        a[i] = s - s2;
        pref[i] = pref[i - 1] + a[i];
    }
    cout << "!" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    return 0;
}
