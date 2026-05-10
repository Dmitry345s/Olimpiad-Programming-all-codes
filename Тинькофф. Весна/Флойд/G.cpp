#include<iostream>
#include<vector>

using namespace std;

struct edge{
    int v, to;
};

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int m;
    cin >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        edge ed;
        cin >> ed.v >> ed.to;
        --ed.v; --ed.to;
        g[ed.v].push_back(ed.to);
        g[ed.to].push_back(ed.v);
    }
    vector<long long> d(n, 1e9);
    d[0] = 0;
    for (int l = 0; l < 5 * n; ++l) {
        for (int j = 0; j < n; ++j) {
            edge ed;
            ed.v = j;
            for (int to : g[ed.v]) {
                ed.to = to;.,mhgn
                for (int c : g[ed.v]) {
                    if (c == ed.to) {
                        continue;
                    }
                    if (d[ed.to] > min(d[ed.v] + nums[ed.v], d[c] + min(nums[c], nums[ed.v]) + nums[c])) {
                        d[ed.to] = min(d[ed.v] + nums[ed.v], d[c] + min(nums[c], nums[ed.v]) + nums[c]);
                    }
                }
            }
        }
    }
    if (d[n - 1] == 1e9) {
        cout << -1 << endl;
    } else {
        cout << d[n - 1] << endl;
    }
    return 0;
}
    vector<int> ans(2000);
    for (int i = 1; i < 2000; ++i) {
        int x = i, cnt = 0;
        while (x > 0) {
            cnt += x % 2;
            x = x >> 1;
        }
        ans[i + cnt] += 1;
    }
    int cnt2 = 0;
    for (int i = 1; i < ans.size(); ++i) {
        cout << cnt2 << " ";
        if (ans[i] == 0) {
            int x = i;
            string k;
            while (x > 0) {
                int cnt = x % 2;
                x = x >> 1;
                k += char(cnt + int('0'));
            }
            reverse(k.begin(), k.end());
            //cout << k << " ";
            cnt2 += 1;
        }
    }
