#include<bits/stdc++.h>

#define int long double

using namespace std;

struct Line {
    int a, b, c;
    Line() {
        a = 0;
        b = 0;
        c = 0;
    }
};

signed main() {
    int n, t;
    cin >> n >> t;
    vector<Line> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].a >> all[i].b >> all[i].c;
    }
    for (int i = 0; i < t; ++i) {
        Line now;
        cin >> now.a >> now.b >> now.c;
        vector<array<int, 3>> to_s(n);
        for (int j = 0; j < n; ++j) {
            int x = (now.b * all[j].c - all[j].b * now.c) / (all[j].b * now.a - all[j].a * now.b);
            int y = (now.c * all[j].a - all[j].c * now.a) / (all[j].b * now.a - all[j].a * now.b);
            to_s[j] = {x, y, j};
        }
        sort(to_s.begin(), to_s.end());
        int ans = 1e18;
        for (int j = 1; j < n; ++j) {
            int j2 = to_s[j][2];
            int j3 = to_s[j - 1][2];
            int x = (all[j3].b * all[j2].c - all[j2].b * all[j3].c) / (all[j2].b * all[j3].a - all[j2].a * all[j3].b);
            int y = (all[j3].c * all[j2].a - all[j2].c * all[j3].a) / (all[j2].b * all[j3].a - all[j2].a * all[j3].b);
            int coun = abs(now.a * x + now.b * y + now.c) / sqrtl(now.a * now.a + now.b * now.b);
            ans = min(ans, coun);
        }
        cout << setprecision(20) << ans << endl;
    }
    return 0;
}
