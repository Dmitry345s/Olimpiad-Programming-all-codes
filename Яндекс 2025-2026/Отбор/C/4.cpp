#include<bits/stdc++.h>

using namespace std;

const int MAX = 100;
string prec[MAX];

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    prec[0] = "b";
    for (int i = 1; i < MAX; ++i) {
        prec[i] = prec[i - 1];
        if (i % 3 == 1) {
            prec[i].push_back('c');
            prec[i].insert(prec[i].begin(), 'a');
        } else if (i % 3 == 2) {
            prec[i].push_back('a');
            prec[i].insert(prec[i].begin(), 'c');
        } else {
            prec[i].push_back('b');
            prec[i].insert(prec[i].begin(), 'b');
        }
    }
    for (int i = 0; i < n; ++i) {
        //cout << prec[i] << endl;
        if (s == prec[i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
