#include<iostream>
#include<vector>

using namespace std;

long long mod = 998244353;
vector<vector<long long>> c_k_n(2000, vector<long long> (2000));
int main(){
    for (int i = 0; i < 2000; ++i){
        for (int j = 0; j < 2000; ++j){
            if (i == j || j == 0){
                c_k_n[i][j] = 1;
            } else if (j > i){
                c_k_n[i][j] = 0;
            } else{
                c_k_n[i][j] = (c_k_n[i - 1][j] + c_k_n[i - 1][j - 1]) % mod;
            }
        }
    }
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    vector<long long> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; --i){
        if (a[i] <= 0){
            continue;
        }
        for (int j = i + a[i] + 1; j <= n; ++j){
            dp[i] += (c_k_n[j - i - 1][a[i]] * dp[j]) % mod;
        }
        dp[i] %= mod;
    }
    long long cnt = 0;
    for (int i = 0; i < n; ++i){
        cnt += dp[i];
        cnt %= mod;
    }
    cout << cnt << endl;
    return 0;
}
