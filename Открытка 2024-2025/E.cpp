#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 1;
vector<int> all[MAX];
int a[MAX];

void solve(int l, int r) {
    if (l + 1 == r) {
        if (a[l] == 0) {
            all[l].push_back(r);
        }
        return;
    }
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
    //cout << "# " << l << " " << r << endl;
    vector<int> cnt(r - l + 1);
    vector<int> left(m - l + 1);
    left.back() = -1;
    for (int i = m - 1; i >= l; --i) {
        left[i - l] = max(left[i - l + 1], a[i]);
    }
    vector<int> right(r - m + 1);
    right[0] = -1;
    for (int i = m; i < r; ++i) {
        right[i - m + 1] = max(right[i - m], a[i]);
    }
    int in = m;
    int rcnt = 0;
    for (int i = m - 1; i >= l; --i) {
        if (left[i - l] > (r - l)) break;
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) {
            rcnt++;
        }
        int rs = left[i - l] + i + 1;
        if (rs <= m || rs > r) continue;
        if (right[rs - m] >= left[i - l]) continue;
        while (in < rs) {
            cnt[a[in]]++;
            if (cnt[a[in]] == 2) {
                rcnt++;
            }
            in++;
        }
        while (in > rs) {
            --in;
            cnt[a[in]]--;
            if (cnt[a[in]] == 1) {
                rcnt--;
            }
        }
        if (rcnt == 0) {
            all[i].push_back(rs);
            //cout << "1 " << i << " " << rs << endl;
        }
    }
    in = m - 1;
    rcnt = 0;
    cnt.assign(r - l + 1, 0);
    for (int i = m; i < r; ++i) {
        if (right[i - m + 1] > (r - l)) break;
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) {
            rcnt++;
        }
        int ls = i - right[i - m + 1];
        if (ls < l || ls > m - 1) continue;
        if (left[ls - l] >= right[i - m + 1]) continue;
        while (in >= ls) {
            cnt[a[in]]++;
            if (cnt[a[in]] == 2) {
                rcnt++;
            }
            in--;
        }
        while (in < ls - 1) {
            ++in;
            if (cnt[a[in]] == 2) {
                rcnt--;
            }
            cnt[a[in]]--;
        }
        if (rcnt == 0) {
            all[ls].push_back(i + 1);
            //cout << ls << " " << i + 1 << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int g;
    cin >> g;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    solve(0, n);
    for (int i = 0; i < q; ++i) {
        int li, xi;
        cin >> li >> xi;
        --li;
        int ri = li + xi;
        int cnt = lower_bound(all[li].begin(), all[li].end(), ri) - all[li].begin();
        if (cnt == (int)all[li].size()) {
            cout << -1 << " " << 0 << endl;
        } else {
            cout << all[li][cnt] - li << " " << (int)all[li].size() - cnt << endl;
        }
    }
    return 0;
}
