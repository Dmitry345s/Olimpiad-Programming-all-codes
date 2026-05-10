#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<pair<int, int>> st;
    vector<int> cnt(26);
    vector<pair<int, int>> now;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        now.push_back({c, i});
    }
    sort(now.begin(), now.end());
    for (int i = 0; i < n; ++i) {
        //int j = now[i].second;
        int j = (i + n / 2) % n;
        ans[now[j].second] = now[i].first;
    }
    for (int i = 0; i < n; ++i) {
        if ((char)(ans[i] + 'a') == s[i]) {
            cout << "Impossible" << endl;
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (char)(ans[i] + 'a');
    }
    return 0;
}
