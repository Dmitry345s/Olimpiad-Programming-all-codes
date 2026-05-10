#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

signed main() {
    vector<int> pows(11);
    pows[0] = 1;
    for (int i = 1; i < 11; ++i) {
        pows[i] = pows[i - 1] * 4;
    }
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = INF;
    vector<vector<int>> all(4 * n, vector<int> (4 * n));
    for (int mask = 0; mask < pows[n]; ++mask) {
        int xn = 0;
        int yn = 0;
        int mny = 0;
        int mxy = 0;
        int mnx = 0;
        int mxx = 0;
        int ch = 0;
        pair<int, int> wh = {-1, 0};
        for (int i = 0; i < n; ++i) {
            int c = ((mask / pows[i]) % 4) + 1;
            if (s[i] == 'L') {
                swap(wh.first, wh.second);
                wh.first *= -1;
            } else {
                swap(wh.first, wh.second);
                wh.second *= -1;
            }
            for (int j = 0; j < c; ++j) {
                xn += wh.first;
                yn += wh.second;
                all[xn + 2 * n][yn + 2 * n]++;
                ch = max(all[xn + 2 * n][yn +  2 * n], ch);
            }
            mny = min(mny, yn);
            mnx = min(mnx, xn);
            mxy = max(mxy, yn);
            mxx = max(mxx, xn);
        }
        int fl = (xn == 0 && yn == 0) && (ch <= 1);
        if (fl) {
            ans = min(ans, (mxx - mnx) * (mxy - mny));
        }
        wh = {-1, 0};
        xn = 0;
        yn = 0;
        for (int i = 0; i < n; ++i) {
            int c = ((mask / pows[i]) % 4) + 1;
            if (s[i] == 'L') {
                swap(wh.first, wh.second);
                wh.first *= -1;
            } else {
                swap(wh.first, wh.second);
                wh.second *= -1;
            }
            for (int j = 0; j < c; ++j) {
                xn += wh.first;
                yn += wh.second;
                all[xn + 2 * n][yn + 2 * n]--;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
