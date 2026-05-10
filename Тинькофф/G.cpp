#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<int> z_func(string s) {
    int n = s.size();
    vector<int> ans(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            ans[i] = min(r - i + 1, ans[i - l]);
        while (i + ans[i] < n && s[ans[i]] == s[i + ans[i]])
            ans[i] += 1;
        if (i + ans[i] - 1 > r) {
            r = i + ans[i] - 1;
            l = i;
        }
    }
    return ans;
}

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    string t;
    cin >> t;
    vector<int> dp(n + 1);
    dp[0] = 0;
    int minm = 1000000000;
    for (int i = 1; i < n + 1; ++i){
        minm = 1000000000;
        string s = t.substr(0, i);
        reverse(s.begin(), s.end());
        vector<int> z = z_func(s);
        int revers = z.size() - 1;
        for (int j = 0; j < z.size(); ++j){
            int j_t = revers - j;
            if (z[j] > 0){
                minm = min(minm, dp[i - min(j, z[j])] + b);
            }
        }
        if (minm != 100000000){
            dp[i] = min(dp[i - 1] + a, minm);
        } else{
            dp[i] = dp[i - 1] + a;
        }
    }
    cout << dp.back() << endl;
}
