#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < (n + 2) / 3; ++i) {
        string t;
        cin >> t;
        s += t;
    }
    int i = 0;
    vector<int> now;
    vector<char> p;
    while (i < n) {
        now.push_back(1);
        p.push_back(s[i]);
        i++;
        while (i < n && s[i] == s[i - 1]) {
            now.back()++;
            i++;
        }
    }
    while ((int)now.size() >= 2 && now.back() == 1 && now[(int)now.size() - 2] % 3 != 0) {
        now.pop_back();
        p.pop_back();
    }
    if ((int)now.size() == 1) {
        int ans = 0;
        for (int i = 0; i < (int)now.size(); ++i) {
            ans += now[i];
        }
        int cnt = -1;
        cout << ans << endl;
        for (int i = 0; i < (int)now.size(); ++i) {
            for (int j = 0; j < now[i]; ++j) {
                cout << p[i];
                cnt++;
                if (cnt % 3 == 2) {
                    cout << endl;
                }
            }
        }
        return 0;
    }
    int u = (int)now.size();
    if ((int)now.size() >= 3 && now[u - 3] % 3 == 2 && now[u - 2] == 1 && now[u - 1] == 1) {
        int ans = 0;
        for (int i = 0; i < (int)now.size() - 3; ++i) {
            now[i] = now[i] - now[i] % 3;
            ans += now[i];
        }
        ans += now[u - 3];
        now[u - 1] = 0;
        now[u - 2] = 0;
        int cnt = -1;
        cout << ans << endl;
        for (int i = 0; i < (int)now.size(); ++i) {
            for (int j = 0; j < now[i]; ++j) {
                cout << p[i];
                cnt++;
                if (cnt % 3 == 2) {
                    cout << endl;
                }
            }
        }
        return 0;
    }
    for (int i = 0; i < (int)now.size() - 2; ++i) {
        now[i] = now[i] - now[i] % 3;
    }
    if (now.back() == 1 && now[(int)now.size() - 2] % 3 != 0)  {
        now.back() = 0;
    } else {
        now[(int)now.size() - 2] = now[(int)now.size() - 2] - now[(int)now.size() - 2] % 3;
    }
    int ans = 0;
    for (int i = 0; i < (int)now.size(); ++i) {
        ans += now[i];
    }
    int cnt = -1;
    cout << ans << endl;
    for (int i = 0; i < (int)now.size(); ++i) {
        for (int j = 0; j < now[i]; ++j) {
            cout << p[i];
            cnt++;
            if (cnt % 3 == 2) {
                cout << endl;
            }
        }
    }
    return 0;
}
