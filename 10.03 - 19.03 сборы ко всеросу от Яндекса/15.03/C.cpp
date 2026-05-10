#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1e4;

vector<int> g[MAX];
int used[MAX];
int fl = 1;

void dfs(int v, int num) {
    used[v] = num;
    for (int to : g[v]) {
        if (used[to]) {
            if (used[to] == used[v]) {
                fl = 0;
            }
        } else {
            dfs(to, ((used[v] - 1) ^ 1) + 1);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (b[i] <= a[j] || b[j] <= a[i] || (a[i] <= a[j] && b[j] <= b[i]) || (a[j] <= a[i] && b[i] <= b[j])) continue;
            g[i].push_back(j);
        }
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, 1);
            ans *= 2;
            ans %= MOD;
        }
    }
    cout << ans * fl << endl;
}
