#include<bits/stdc++.h>

using namespace std;

const int MAX = 4096;
int a[MAX], b[MAX];

vector<pair<int, int>> ans;

void revers(int l, int r) {
    int in1 = l, in2 = r - 1;
    while (in1 < in2) {
        ans.push_back({in1, in2});
        in1++;
        in2--;
    }
    reverse(a + l, a + r);
}

void solve(int l, int r) {
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
    revers(l, m);
    revers(m, r);
    vector<int> all;
    for (int i = l; i < r; ++i) {
        all.push_back(a[i]);
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < (int)all.size(); ++i) {
        vector<int> pref(r - l + 1);
        pref[0] = -1;
        pref[1] = l + i;
        for (int j = l + i + 1; j < r; ++j) {
            pref[j - l - i + 1] = pref[j - l - i];
            if (a[j] > a[pref[j - l - i + 1]]) {
                pref[j - l - i + 1] = j;
            }
        }
        for (int j = l; j < r; ++j) {
            if (a[j] == all[i]) {
                int now = j - 1;
                while (now >= i + l) {
                    swap(a[now + 1], a[pref[now - l - i + 1]]);
                    ans.push_back({pref[now - l - i + 1], now + 1});
                    now = pref[now - l - i + 1] - 1;
                }
                break;
            }
        }
    }
    /*cout << "# " << l << " " << r << endl;
    for (int i = l; i < r; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;*/
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    solve(0, n);
    vector<pair<int, int>> rans = ans;
    ans.clear();
    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
    }
    solve(0, n);
    reverse(ans.begin(), ans.end());
    for (auto now : ans) {
        rans.push_back(now);
    }
    assert((int)rans.size() <= 300000);
    cout << (int)rans.size() << endl;
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i].first + 1 << " " << rans[i].second + 1 << endl;
    }
    return 0;
}
