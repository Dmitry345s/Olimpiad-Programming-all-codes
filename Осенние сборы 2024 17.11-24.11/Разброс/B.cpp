#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<string, string>> all(n);
    array<int, 3> nowmax = {(int)1e9, (int)1e9, (int)1e9};
    int cnt = 0;
    int last = 0;
    for (int i = 0; i < n; ++i) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        all[i] = {s1, s2};
        array<int, 3> date = {(s3[6] - '0') * 1000 + (s3[7] - '0') * 100 + (s3[8] - '0') * 10 + (s3[9] - '0'), (s3[3] - '0') * 10 + (s3[4] - '0'), (s3[0] - '0') * 10 + (s3[1] - '0')};
        if (date < nowmax) {
            cnt = 1;
            nowmax = date;
            last = i;
        } else if (date == nowmax) {
            cnt++;
        }
    }
    if (cnt == 1) {
        cout << all[last].first << " " << all[last].second << " " << nowmax[2] / 10 % 10 << nowmax[2] % 10 << "." << nowmax[1] / 10 % 10 << nowmax[1] % 10 << "." << nowmax[0] / 1000 % 10 << nowmax[0] / 100 % 10 << nowmax[0] / 10 % 10 << nowmax[0] % 10 << endl;
    } else {
        cout << cnt << endl;
    }
    return 0;
}
