#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(50000);
vector<bool> used(50000);
vector<int> d(50000, -1e9);
vector<vector<int>> dp(500000, {0, 0, 0});
vector<int> ans;

void dfs1(int v, int p = -1) {
    used[v] = true;
    int maxm = -1e9;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs1(to, v);
            maxm = max(maxm, d[to] + 1);
        }
    }
    if (g[v].size() == 1 && g[v][0] == p) {
        d[v] = 0;
    } else {
        d[v] = maxm;
    }
}

void dfs2(int x, int v = 0) {
    used[v] = true;
    if (d[v] == x) {
        ans.push_back(v);
        dp[v][0] = 1;
        dp[v][1] = 0;
        dp[v][2] = 2 * x + 1;
    } else if (d[v] < x) {
        dp[v][0] = 0;
        dp[v][1] = 100000;
        dp[v][2] = x - d[v];
    } else {
        int sum = 0, check1 = 100000;
        vector<int> check2;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to]) {
                dfs2(x, to);
                sum += dp[to][0];
                check1 = min(check1, dp[to][1] + 1);
                check2.push_back(dp[to][2] - 1);
            }
        }
        int ans_ch2 = 2 * x + 1 - check1;
        for (int i = 0; i < check2.size(); ++i) {
            if (check1 > check2[i]) {
                ans_ch2 = min(check2[i], ans_ch2);
            }
        }
        if (ans_ch2 == 0 || (ans_ch2 < x + 1 && v == 0)) {
            ans.push_back(v);
            dp[v][0] = sum + 1;
            dp[v][1] = 0;
            dp[v][2] = 2 * x + 1;
        } else {
            dp[v][0] = sum;
            dp[v][1] = check1;
            dp[v][2] = ans_ch2;
        }
    }
}
int main() {
    int n, k;
    cin >> n >> k;
    int i, j;
    for (int l = 0; l < n - 1; ++l) {
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    dfs1(0);
    vector<int> answer;
    int l = 0, r = n;
    while (l + 1 < r) {
        for (int i = 0; i < n; ++i) {
            used[i] = false;
            dp[i] = {0, 0, 0};
        }
        ans.clear();
        int m = (l + r) / 2;
        dfs2(m);
        if (dp[0][0] <= k) {
            answer = ans;
            r = m;
        } else {
            l = m;
        }
    }
    for (int i = 0; i < n; ++i) {
        used[i] = false;
        dp[0] = {0, 0, 0};
    }
    ans.clear();
    dfs2(l);
    if (dp[0][0] <= k) {
        cout << l << endl;
        answer = ans;
    } else {
        for (int i = 0; i < n; ++i) {
            used[i] = false;
            dp[0] = {0, 0, 0};
        }
        ans.clear();
        dfs2(r);
        answer = ans;
        cout << r << endl;
    }
    vector<bool> more(n, false);
    for (int i = 0; i < answer.size(); ++i) {
        more[answer[i]] = true;
    }
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] + 1 << " ";
    }
    int checker = 0;
    i = 0;
    while (checker < k - answer.size()) {
        if (!more[i]) {
            cout << i + 1 << " ";
            checker += 1;
        }
        i += 1;
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
            used[i] = false;
            dp[0] = {0, 0, 0};
        }
    ans.clear();
    dfs2(2);
    return 0;
}
