#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, l, k;
    cin >> n >> l >> k;
    vector<int> d(n);
    for (int i = 0; i < n; ++i){
        cin >> d[i];
    }
    vector<long long> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    d.push_back(l);
    a.push_back(0);
    vector<vector<long long>> dp(n + 1, vector<long long> (n, 1500000000));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i){
        for (int j = 0; j < i; ++j){
            for (int l = 0; l <= j; ++l){
                dp[i][j] = min(dp[i][j], dp[i - l - 1][j - l] + (d[i] - d[i - l - 1]) * a[i - l - 1]);
            }
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    long long ans = 1500000000;
    for (int i = 0; i <= k; ++i){
        ans = min(ans, dp[n][i]);
    }
    cout << ans << endl;
    return 0;
}
