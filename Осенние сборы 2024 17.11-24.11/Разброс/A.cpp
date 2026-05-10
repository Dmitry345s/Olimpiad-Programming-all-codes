#include<bits/stdc++.h>

using namespace std;

int conv(string s) {
    return (s[0]- '0') * 10 * 60 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4]- '0');
}

string conv2(int c) {
    string s = "00:00";
    int h = c / 60;
    h %= 24;
    s[0] = (h / 10 % 10 + '0');
    s[1] = (h % 10 + '0');
    s[3] = (c % 60 / 10 % 10 + '0');
    s[4] = (c % 60 % 10 + '0');
    return s;
}

signed main() {
    int now;
    string s;
    cin >> s;
    now = conv(s);
    int n;
    cin >> n;
    cout << s << endl;
    for (int i = 0; i < n - 1; ++i) {
        int a;
        cin >> a;
        now += a;
        cout << conv2(now) << endl;
    }
    return 0;
}
