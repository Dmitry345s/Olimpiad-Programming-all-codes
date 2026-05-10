#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> cnt(2e6);
    set<int> st;
    for (int i = 1; i <= n - 1; ++i) {
        st.insert(i);
    }
    for (int i = 1; i < n; ++i) {
        int x = abs(a[i] - a[i - 1]);
        cnt[x]++;
        st.erase(x);
    }
    vector<pair<int, int>> ans;
    for (int i = 1; i < n - 1; ++i) {
        int x1 = abs(a[i] - a[i - 1]);
        int x2 = abs(a[i] - a[i + 1]);
        cnt[x1]--;
        if (cnt[x1] == 0 && 1 <= x1 && x1 <= n - 1) {
            st.insert(x1);
        }
        cnt[x2]--;
        if (cnt[x2] == 0 && 1 <= x2 && x2 <= n - 1) {
            st.insert(x2);
        }
        if ((int)st.size() != 2) {
            cnt[x1]++;
            if (cnt[x1] == 1) {
                st.erase(x1);
            }
            cnt[x2]++;
            if (cnt[x2] == 1) {
                st.erase(x2);
            }
            continue;
        }
        auto it = st.begin(), it2 = it;
        it2++;
        if (abs(a[i - 1] - a[i + 1]) == *it + *it2) {
            ans.push_back({i, min(a[i - 1], a[i + 1]) + *it});
            ans.push_back({i, min(a[i - 1], a[i + 1]) + *it2});
        }
        if (abs(a[i - 1] - a[i + 1]) == *it2 - *it) {
            ans.push_back({i, min(a[i - 1], a[i + 1]) - *it});
            ans.push_back({i, max(a[i - 1], a[i + 1]) + *it});
        }
        cnt[x1]++;
        if (cnt[x1] == 1) {
            st.erase(x1);
        }
        cnt[x2]++;
        if (cnt[x2] == 1) {
            st.erase(x2);
        }
    }
    int x1 = abs(a[0] - a[1]);
    cnt[x1]--;
    if (cnt[x1] == 0 && 1 <= x1 && x1 <= n - 1) {
        st.insert(x1);
    }
    if ((int)st.size() == 1) {
        ans.push_back({0, a[1] - *st.begin()});
        ans.push_back({0, a[1] + *st.begin()});
    }
    cnt[x1]++;
    if (cnt[x1] == 1) {
        st.erase(x1);
    }
    int x2 = abs(a[n - 1] - a[n - 2]);
    cnt[x2]--;
    if (cnt[x2] == 0 && 1 <= x2 && x2 <= n - 1) {
        st.insert(x2);
    }
    if ((int)st.size() == 1) {
        ans.push_back({n - 1, a[n - 2] - *st.begin()});
        ans.push_back({n - 1, a[n - 2] + *st.begin()});
    }
    cnt[x1]++;
    if (cnt[x1] == 1) {
        st.erase(x1);
    }
    sort(ans.begin(), ans.end());
    int rans = 0;
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (a[ans[i].first] != ans[i].second) {
            rans++;
        }
        //cout << ans[i].first + 1 << " " << ans[i].second << endl;
    }
    cout << rans << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (a[ans[i].first] != ans[i].second) {
            cout << ans[i].first + 1 << " " << ans[i].second << endl;
        }
    }
    return 0;
}
