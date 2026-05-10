#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

signed main() {
    int n;
    cin >> n;
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        st.insert({0, i});
    }
    vector<int> a(n);
    vector<int> ls(n);
    vector<int> lupd(n, -1);
    int cnt = 0;
    while (st.size() > 1 && cnt < 2 * n) {
        cnt++;
        int v = st.begin()->second;
        int v2 = st.rbegin()->second;
        st.erase({ls[v], v});
        st.erase({ls[v2], v2});
        cout << "? " << v + 1 << " " << v2 + 1 << endl;
        int ans;
        cin >> ans;
        if (ans == ls[v2]) {
            a[v2] = ans;
            ls[v] = max(ls[v], ans);
            st.insert({ls[v], v});
        } else if (ans < ls[v2]) {
            a[v] = ans;
            st.insert({ls[v2], v2});
        } else {
            if (lupd[v2] != -1) {
                a[lupd[v2]] = ls[lupd[v2]];
                st.erase({ls[lupd[v2]], lupd[v2]});
            }
            ls[v] = ans;
            lupd[v] = v2;
            lupd[v2] = v;
            ls[v2] = ans;
            st.insert({ls[v], v});
            st.insert({ls[v2], v2});
        }
    }
    cout << "! ";
    for (int i = 0; i < n; ++i) {
        if (!a[i]) {
            cout << ls[i] << " ";
            continue;
        }
        cout << a[i] << " ";
    }
    cout << endl;
}
