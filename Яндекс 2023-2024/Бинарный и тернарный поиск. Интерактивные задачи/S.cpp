#include<bits/stdc++.h>

using namespace std;

int cnt = 0;

void ask(long long a, int & ans) {
    cnt++;
    assert(cnt <= 75);
    cout << "query " << a << endl;
    cin >> ans;
}

signed main() {
    int last;
    ask(0, last);
    if (last == 0) {
        cout << "answer " << 0 << endl;
        return 0;
    }
    long long p = 1;
    string ans;
    for (int i = 0; i < 18; ++i) {
        int l = 0, r = 10;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            long long q = m * p;
            int k;
            ask(q, k);
            if (k <= last) {
                r = m;
            } else {
                l = m;
            }
        }
        if (r == 10) {
            ans.push_back('0');
        } else {
            ans.push_back(char(((int)'0') + (10 - r)));
        }
        p *= 10;
    }
    while (ans.back() == '0') {
        ans.pop_back();
    }
    reverse(ans.begin(), ans.end());
    cout << "answer " << ans << endl;
    return 0;
}
