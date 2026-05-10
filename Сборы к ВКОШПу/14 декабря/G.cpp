#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _;
    cin >> _;
    while(_--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> cnt(10);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        cout << "- " << 0 << endl;
        vector<int> ncnt(10);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            ncnt[a[i]]++;
        }
        if (ncnt == cnt) {
            cout << "- " << 0 << endl;
            ncnt.assign(10, 0);
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
                ncnt[a[i]]++;
            }
        }
        int ch = 0;
        for (int i = 0; i < 10; ++i) {
            if (ncnt[i] - 1 == cnt[i]) {
                ch = i;
            }
        }
        vector<int> now;
        for (int i = 0; i < n; ++i) {
            if (a[i] != ch) {
                now.push_back(i);
            }
        }
        cout << "- " << (int)now.size() << " ";
        for (int v : now) {
            cout << v + 1 << " ";
        }
        cout << endl;
        vector<int> nncnt(10);
        for (int i = 0; i < n - (int)now.size(); ++i) {
            cin >> a[i];
            nncnt[a[i]]++;
        }
        if (nncnt[ch] == ncnt[ch]) {
            nncnt.assign(10, 0);
            cout << "- " << 0 << endl;
            int fl = -1;
            for (int i = 0; i < n - (int)now.size(); ++i) {
                cin >> a[i];
                if (a[i] != ch) {
                    fl = i;
                }
                nncnt[a[i]]++;
            }
            cout << "! " << fl + 1 << endl;
        } else {
            for (int i = 0; i < n; ++i) {
                if (a[i] != ch) {
                    cout << "! " << i + 1 << endl;
                    break;
                }
            }
        }
    }
    return 0;
}

