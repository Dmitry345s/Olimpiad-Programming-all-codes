#include<bits/stdc++.h>

using namespace std;

signed main() {
    int h, w, q;
    cin >> h >> w >> q;
    vector<vector<int>> f(h, vector<int> (w));
    vector<pair<int, int>> ch(h * w);
    for (int i = 0; i < h * w; ++i) {
        int x, y;
        cin >> x >> y;
        ch[i] = {x, y};
    }
    vector<array<int, 4>> df(h * w);
    vector<int> ch2(h * w);
    int ans = 0;
    df[0] = {ch[0].first, ch[0].first, ch[0].second, ch[0].second};
    ch2[0] = 1;
    ans++;
    for (int i = 1; i < h * w; ++i) {
        df[i] = {min(df[i - 1][0], ch[i].first), max(df[i - 1][1], ch[i].first), min(df[i - 1][2], ch[i].second), max(df[i - 1][3], ch[i].second)};
        if ((df[i][1] - df[i][0] + 1) * (df[i][3] - df[i][2] + 1) == i + 1) {
            ch2[i] = 1;
            ans++;
        }
    }
    for (int _ = 0; _ < q; ++_) {
        int a, b;
        cin >> a >> b;
        swap(ch[a], ch[b]);
        if (a > b) {
            swap(a, b);
        }
        if (a == 0) {
            df[0] = {ch[0].first, ch[0].first, ch[0].second, ch[0].second};
            a++;
        }
        for (int i = a; i <= b; ++i) {
            df[i] = {min(df[i - 1][0], ch[i].first), max(df[i - 1][1], ch[i].first), min(df[i - 1][2], ch[i].second), max(df[i - 1][3], ch[i].second)};
            if ((df[i][1] - df[i][0] + 1) * (df[i][3] - df[i][2] + 1) == i + 1) {
                if (ch2[i] == 0) {
                    ch2[i] = 1;
                    ans++;
                }
            } else {
                if (ch2[i] == 1) {
                    ch2[i] = 0;
                    ans--;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
