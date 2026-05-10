#include<bits/stdc++.h>

using namespace std;

vector<char> st;
int n;
int total;

bool dfs(int i, vector<pair<array<int, 2>, string>> & all, vector<char> & ans, int now) {
    if (i >= (int)all.size()) return true;
    now = max(now, total);
    if (now > all[i].first[0] && ans[all[i].first[0]] == '#' || all[i].first[0] >= now && st[all[i].first[0]] == '#') {
        total = all[i].first[0] - 1;
        now = max(now, total);
        int fl = true;
        for (int j = all[i].first[0]; j < all[i].first[0] + all[i].first[1]; ++j) {
            if (j < now && ans[j] != '#' && ans[j] != all[i].second[j - all[i].first[0]] || j >= now && st[j] != '#' && st[j] != all[i].second[j - all[i].first[0]]) {
                fl = false;
                break;
            }
            ans[j] = all[i].second[j - all[i].first[0]];
        }
        if (fl) {
            fl = dfs(i + 1, all, ans, max(now, all[i].first[0] + all[i].first[1]));
        }
        if (!fl) {
            reverse(all[i].second.begin(), all[i].second.end());
            for (int j = all[i].first[0]; j < all[i].first[0] + all[i].first[1]; ++j) {
                if (j < now && ans[j] != '#' && ans[j] != all[i].second[j - all[i].first[0]] || j >= now && st[j] != '#' && st[j] != all[i].second[j - all[i].first[0]]) {
                    return false;
                }
                ans[j] = all[i].second[j - all[i].first[0]];
            }
            return dfs(i + 1, all, ans, max(now, all[i].first[0] + all[i].first[1]));
        }
        return fl;
    } else {
        if (all[i].first[0] < now && ans[all[i].first[0]] != all[i].second[0] || all[i].first[0] >= now && st[all[i].first[0]] != all[i].second[0]) {
            reverse(all[i].second.begin(), all[i].second.end());
        }
        for (int j = all[i].first[0]; j < all[i].first[0] + all[i].first[1]; ++j) {
            if (j < now && ans[j] != '#' && ans[j] != all[i].second[j - all[i].first[0]] || j >= now && st[j] != '#' && st[j] != all[i].second[j - all[i].first[0]]) {
                return false;
            }
            ans[j] = all[i].second[j - all[i].first[0]];
        }
        return dfs(i + 1, all, ans, max(now, all[i].first[0] + all[i].first[1]));
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> n >> q;
    vector<char> ans(n, '#');
    vector<pair<array<int, 2>, string>> all;
    for (int i = 0; i < q; ++i) {
        int b, k;
        string s;
        cin >> b >> k >> s;
        int cnt = 0;
        string t = s;
        reverse(t.begin(), t.end());
        //assert(s == t);
        while (cnt < (k + 1) / 2 && s[cnt] == s[k - 1 - cnt]) {
            cnt++;
        }
        //assert(2 * cnt >= k);
        for (int j = b; j < b + cnt; ++j) {
            if (ans[j] != '#' && ans[j] != s[j - b]) {
                cout << "NO" << endl;
                return 0;
            }
            ans[j] = s[j - b];
        }
        for (int j = b + k - 1; j >= b + k - cnt; --j) {
            if (ans[j] != '#' && ans[j] != s[j - b]) {
                cout << "NO" << endl;
                return 0;
            }
            ans[j] = s[j - b];
        }
        for (int i = 0; i < cnt; ++i) s.pop_back();
        reverse(s.begin(), s.end());
        for (int i = 0; i < min(cnt, (int)s.size()); ++i) s.pop_back();
        reverse(s.begin(), s.end());
        b += cnt;
        k -= min(k, 2 * cnt);
        if (k == 0) continue;
        all.push_back({{b, k}, s});
        //cout << b << " " << k << " " << s << endl;
    }
    st = ans;
    total = 0;
    sort(all.begin(), all.end());
    int fl = dfs(0, all, ans, 0);
    if (fl) {
        cout << "YES" << endl;
        for (int i = 0; i < n; ++i) {
            if (ans[i] == '#') {
                cout << 'a';
            } else {
                cout << ans[i];
            }
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
