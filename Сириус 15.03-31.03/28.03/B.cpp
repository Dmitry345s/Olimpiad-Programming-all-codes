#include<bits/stdc++.h>

using namespace std;

int MAX = 2e6;
vector<vector<int>> g(MAX);
vector<char> tp(MAX);
vector<int> dp(MAX);
int cnt = 0;
int flag = 0;
char start;
vector<int> to_get;

void dfs(int v) {
    cnt++;
    int ch = 0;
    for (int to : g[v]) {
        if (tp[v] != tp[to]) continue;
        dfs(to);
        ch++;
    }
    if (ch == 0) {
        to_get.push_back(v);
    }
}

void dfs2(int v) {
    dp[v] = (g[v].size() == 2);
    for (int to : g[v]) {
        dfs2(to);
        dp[v] += dp[to];
    }
}
int cnt2 = 1e9;

void dfs3(int v) {
    if (g[v].size() < 2) {
        cnt2 = min(dp[0] - dp[v], cnt2);
    }
    for (int to : g[v]) {
        dfs3(to);
    }
}

signed main() {
    string s;
    cin >> s;
    vector<char> p;
    int n = 0;
    vector<int> st;
    int t = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'a' || s[i] == 'i') {
            tp[t] = s[i];
            if (st.size() != 0) {
                g[st.back()].push_back(t);
            }
            continue;
        }
        if (s[i] == '(') {
            st.push_back(t);
            ++t;
        } else if (s[i] == ')') {
            st.pop_back();
        }
        if (s[i] == '?') {
            n++;
        }
    }
    dfs(0);
    dfs2(0);
    dfs3(0);
    cout << n - cnt - cnt2 + flag << endl;
    vector<int> per(n);
    for (int i = 0; i < n; ++i) {
        per[i] = i + 1;
    }
    set<int> sts;
    do {
        vector<int> nums;
        int t = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'a' || s[i] == 'i') {
                nums.push_back(n + (int)s[i]);
            } else if (s[i] == '?') {
                nums.push_back(per[t]);
                t++;
            }
            while (nums.size() >= 2 && nums.back() <= n && nums[nums.size() - 2] <= n) {
                int k1 = nums.back();
                nums.pop_back();
                int k2 = nums.back();
                nums.pop_back();
                char p = (char)(nums.back() - n);
                nums.pop_back();
                if (p == 'i') {
                    nums.push_back(min(k1, k2));
                } else {
                    nums.push_back(max(k1, k2));
                }
            }
        }
        sts.insert(nums[0]);
    } while (next_permutation(per.begin(), per.end()));
    cout << sts.size() << endl;
    return 0;
}
