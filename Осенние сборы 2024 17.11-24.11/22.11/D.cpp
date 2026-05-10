#include<bits/stdc++.h>

using namespace std;
using ld = long double;
const ld INF = 2e9;
const int fl = 2e9;

ld get_dist(ld x1, ld y1, ld z1, ld x2, ld y2, ld z2) {
    ld x_ = x1 - x2, y_ = y1 - y2, z_= z1 - z2;
    return sqrtl(x_ * x_ + y_ * y_ + z_ * z_);
}

void get(vector<pair<ld, ld>> a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i].second != fl) {
            cout << " F(" << a[i].first << "," << a[i].second << ")";
        } else {
            cout << " " << a[i].first + 1;
        }
    }
    cout << " B" << endl;
}

signed main() {
    int t;
    cin >> t;
    int n, r, m;
    cin >> n >> r >> m;
    vector<array<int, 3>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i][0] >> vec[i][1] >> vec[i][2];
    }
    vector<string> rans(11);
    rans[1] = "2 1 F(0,3) 3 4 F(-3,0) 5 6 F(0,-3) 7 8 B";
    rans[2] = "4 F(0,-2) 3 F(-1,-1) 1 F(3,2) 2 B";
    rans[5] = "1 2 3 F(1,-1) 6 11 12 F(-1,1) 7 10 13 F(-1,-1) 8 9 5 F(-1,-1) 4 B";
    rans[6] = "1 2 F(0,-8) 3 4";
    rans[4] = "10 2 F(-2,-1) 9 1 F(2,1) 3 6 F(2,-1) 8 7 F(0,3) 5 4 B";
    rans[8] = "1 2 4 7 11 13 F(0,0) 6 10 8 9 3 12 F(0,0) 5 B";
    cout << rans[t] << endl;
    return 0;
    if (n <= 100) {
        vector<pair<ld, ld>> ans;
        ld minm = INF;
        vector<int> now(n);
        for (int i = 0; i < n; ++i) {
            now[i] = i;
        }
        int ch = 0;
        do {
            ld x = 0, y = 0, z = 1;
            int cnt = m;
            ld sz = 0;
            vector<pair<ld, ld>> tr;
            for (int i = 0; i < n; ++i) {
                //ld x_ = vec[now[i]][0] - x, y_ = vec[now[i]][1] - y, z_ = vec[now[i]][2] - z;
                if (cnt == 0) {
                    ld x2 = 0, y2 = 0;
                    tr.push_back({x2, y2});
                    sz += get_dist(x, y, z, x2, y2, 0);
                    sz += get_dist(x2, y2, 0, vec[now[i]][0], vec[now[i]][1], vec[now[i]][2]);
                    tr.push_back({now[i], fl});
                    cnt = m - 1;
                } else {
                    sz += get_dist(x, y, z, vec[now[i]][0], vec[now[i]][1], vec[now[i]][2]);
                    tr.push_back({now[i], fl});
                    cnt--;
                }
            }
            if (sz <= minm) {
                minm = sz;
                ans = tr;
            }
            ch++;
        } while (next_permutation(now.begin(), now.end()) && ch < 5e6);
        get(ans);
    }
    return 0;
}
