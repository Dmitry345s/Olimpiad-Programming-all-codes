#include<bits/stdc++.h>

using namespace std;

signed main() {
    int l;
    cin >> l;
    vector<string> a;
    string _;
    getline(cin, _);
    string s;
    getline(cin, s);
    int cnt = s.size();
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0) {
            a.push_back("");
        } else {
            if (s[i] == ' ' && s[i - 1] != ' ' || s[i - 1] == ' ' && s[i] != ' ') {
                a.push_back("");
            }
        }
        a.back().push_back(s[i]);
    }
    //cout << cnt << endl;
    //cout << (int)'z' << endl;
    string b = "http://";
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].size() > 7 && cnt > l) {
            int flag = 1;
            for (int j = 0; j < 7; ++j) {
                if (a[i][j] != b[j]) {
                    flag = 0;
                }
            }
            for (int j = 7; j < a[i].size(); ++j) {
                if (a[i][j] != '.' && a[i][j] != '/' && a[i][j] != ':' && !(97 <= (int)a[i][j] && (int)a[i][j] <= 122) && !(0 <= a[i][j] - '0' && a[i][j] - '0' <= 9)) {
                    flag = 0;
                }
            }
            if (flag) {
                int last = 0;
                for (int j = 0; j < a[i].size(); ++j) {
                    if (cnt - a[i].size() + (j + 3) <= l) {
                        last = j;
                    }
                }
                for (int j = 0; j < last; ++j) {
                    cout << a[i][j];
                }
                cout << "...";
                cnt = cnt - a[i].size() + (last + 3);
            } else {
                cout << a[i];
            }
        } else {
            cout << a[i];
        }
    }
    cout << endl;
    cout << max(0, cnt - l) << endl;
    return 0;
}
