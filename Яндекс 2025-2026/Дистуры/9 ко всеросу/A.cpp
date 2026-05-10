#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> ans(k);
    vector<pair<int, int>> gr;
    vector<pair<int, int>> gl;
    for (int i = 0; i < n; ++i) {
        int d, b;
        char c;
        cin >> d >> b >> c;
        if (c == 'D') {
            ans[b] += 2 * (l - d);
            gr.push_back({d, b});
        } else {
            gl.push_back({d, b});
        }
    }
    vector<int> cnt(k);
    int u = 0;
    for (int i = (int)gr.size() - 1; i > 0; --i) {
        u = (u + gr[i].second) % k;
        cnt[u] += gr[i].first - gr[i - 1].first;
    }
    int en = (u + gr[0].second) % k;
    int r = (int)gr.size() - 1;
    u = 0;
    for (int i = (int)gl.size() - 1; i >= 0; --i) {
        int j = upper_bound(gr.begin(), gr.end(), pair<int, int>{gl[i].first, k + 1}) - gr.begin();
        //cout << i << " " << j << endl;
        if (j == 0) {
            ans[gl[i].second] += 2 * gl[i].first;
            continue;
        }
        while (r >= j) {
            u = (u + gr[r].second) % k;
            cnt[u] -= gr[r].first - gr[r - 1].first;
            --r;
        }
        --j;
        ans[gl[i].second % k] += gl[i].first - gr[j].first;
        ans[(en + gl[i].second + k - u) % k] += gl[i].first + gr[0].first;
        //cout << u << " " << gl[i].second << endl;
        for (int st = 0; st < k; ++st) {
            ans[(st + gl[i].second + k - u) % k] += cnt[st];
        }
    }
    for (int i = 0; i < k; ++i) {
        cout << ans[i] / 2;
        if (ans[i] % 2) {
            cout << ".5" << endl;
        } else {
            cout << ".0" << endl;
        }
    }
    return 0;
}
