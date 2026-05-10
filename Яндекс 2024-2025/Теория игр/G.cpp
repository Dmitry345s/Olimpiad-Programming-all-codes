#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e3 + 1;

int ans[MAX];

signed main() {
    ans[1] = 0;
    for (int i = 2; i < MAX; ++i) {
        vector<int> ch(MAX);
        for (int j = (i + 1) / 2; j < i; ++j) {
            ch[ans[j]]++;
        }
        for (int j = 0; j < MAX; ++j) {
            if (ch[j] == 0) {
                ans[i] = j;
                break;
            }
        }
    }
    int a, b, c;
    cin >> a >> b >> c;
    int x = (ans[a] ^ ans[b] ^ ans[c]);
    if (x == 0) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (int j = (c + 1) / 2; j < c; ++j) {
        if ((ans[a] ^ ans[b] ^ ans[j]) == 0) {
            cout << a << " " << b << " " << j << endl;
            return 0;
        }
    }
    for (int j = (a + 1) / 2; j < a; ++j) {
        if ((ans[j] ^ ans[b] ^ ans[c]) == 0) {
            cout << j << " " << b << " " << c << endl;
            return 0;
        }
    }
    for (int j = (b + 1) / 2; j < b; ++j) {
        if ((ans[a] ^ ans[j] ^ ans[c]) == 0) {
            cout << a << " " << j << " " << c << endl;
            return 0;
        }
    }
    return 0;
}
