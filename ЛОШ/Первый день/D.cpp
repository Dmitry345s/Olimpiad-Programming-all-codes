#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void dfs(int v, vector<vector<int>> & g, vector<pair<int, int>> & a) {
    for (int to : g[v]) {
        dfs(to, g, a);
        a[v].first = min(a[v].first, a[to].first);
        a[v].second = max(a[v].second, a[to].second);
    }
    if (g[v].size() == 0) {
        a[v] = {v, v};
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    vector<int> b(n);
    vector<vector<int>> g1(m + n), g2(k + n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        --a[i]; --b[i];
        g1[a[i]].push_back(i + m);
        g2[b[i]].push_back(i + k);
    }
    vector<int> c(m - 1);
    for (int i = 0; i < m - 1; ++i) {
        cin >> c[i];
        --c[i];
        g1[c[i]].push_back(i);
    }
    vector<int> d(k - 1);
    for (int i = 0; i < k - 1; ++i) {
        cin >> d[i];
        --d[i];
        g2[d[i]].push_back(i);
    }
    vector<pair<int, int>> ms(m + n, {1e9, -1});
    vector<pair<int, int>> ks(k + n, {1e9, -1});
    dfs(m - 1, g1, ms);
    dfs(k - 1, g2, ks);
    vector<int> ks2, ks3;
    for (int i = 0; i < k; ++i) {
        ks2.push_back(ks[i].first - k);
        ks3.push_back(ks[i].second - k);
        //cout << ks[i].first - k << " " << ks[i].second - k << endl;
    }
    sort(ks2.begin(), ks2.end());
    sort(ks3.begin(), ks3.end());
    vector<long long> cnt(n + 1), cnt2(n + 1);
    /*for (int i = 0; i < ks3.size(); ++i) {
        cout << ks3[i] << " ";
    }
    cout << endl;*/
    int j = 0;
    cnt[0] = 0;
    for (int i = 1; i < n + 1; ++i) {
        if (i == 1) {
            cnt[i] = 0;
        } else {
            cnt[i] = cnt[i - 1];
        }
        while (j < ks3.size() && ks3[j] == i - 1) {
            ++j;
            ++cnt[i];
        }
    }
    j = ks2.size() - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            cnt2[i] = 0;
        } else {
            cnt2[i] = cnt2[i + 1];
        }
        while (j >= 0 && ks2[j] == i) {
            --j;
            ++cnt2[i];
        }
    }
    cnt2[n] = 0;
    /*for (int i = 0; i < n + 1; ++i) {
        cout << cnt[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n + 1; ++i) {
        cout << cnt2[i] << " ";
    }
    cout << endl;*/
    long long ans = 0, p = k;
    for (int i = 0; i < m; ++i) {
        //cout << ms[i].first - m << " " << ms[i].second - m + 1 << endl;
        ans += p - (cnt[ms[i].first - m] + cnt2[ms[i].second - m + 1]);
    }
    cout << ans << endl;
    return 0;
}
