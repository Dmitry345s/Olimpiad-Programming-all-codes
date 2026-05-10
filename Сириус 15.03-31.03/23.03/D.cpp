#include<bits/stdc++.h>

#define int long long

using namespace std;

bool get(array<int, 4> one, array<int, 4> two) {
    if (two[0] >= one[2] || two[1] >= one[3]) {
        return false;
    }
    swap(two, one);
    if (two[0] >= one[2] || two[1] >= one[3]) {
        return false;
    }
    return true;
}

mt19937 rnd(time(0));

signed main() {
    int n;
    cin >> n;
    vector<array<int, 4>> cs(n);
    vector<int> xs;
    vector<int> ys;
    for (int i = 0; i < n; ++i) {
        cin >> cs[i][0] >> cs[i][1] >> cs[i][2] >> cs[i][3];
        xs.push_back(cs[i][0]);
        xs.push_back(cs[i][2]);
        ys.push_back(cs[i][1]);
        ys.push_back(cs[i][3]);
    }
    /*sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < n; ++i) {
        cs[i][0] = lower_bound(xs.begin(), xs.end(), cs[i][0]) - xs.begin();
        cs[i][2] = lower_bound(xs.begin(), xs.end(), cs[i][2]) - xs.begin();
        cs[i][1] = lower_bound(ys.begin(), ys.end(), cs[i][1]) - ys.begin();
        cs[i][3] = lower_bound(ys.begin(), ys.end(), cs[i][3]) - ys.begin();
    }*/
    int rflag = 1;
    array<int, 4> fu = {-1, -1, -1, -1};
    for (int i = 0; i < min(n - 1, 19 * 1ll); ++i) {
        int flag2 = 0;
        for (int j = 0; j < n; ++j) {
            for (int l = j + 1; l < n; ++l) {
                if (j == l || cs[j] == fu || cs[l] == fu) continue;
                array<int, 4> p;
                p[0] = min(cs[l][0], cs[j][0]);
                p[1] = min(cs[l][1], cs[j][1]);
                p[2] = max(cs[l][2], cs[j][2]);
                p[3] = max(cs[l][3], cs[j][3]);
                int flag = 1;
                for (int k = 0; k < n; ++k) {
                    if (k == l || k == j || cs[k] == fu) continue;
                    if (get(cs[k], p)) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    cs[l] = p;
                    cs[j] = fu;
                    flag2 = 1;
                    break;
                }
            }
            if (flag2) break;
        }
        if (flag2 == 0) {
            rflag = 0;
            break;
        }
    }
    if (rflag) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
