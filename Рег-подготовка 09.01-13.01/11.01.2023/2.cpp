#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> sum(101, 0), ls(101, -1), rs(101, -1);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        if (sum[a[i]] == 0){
            ls[a[i]] = i;
        }
        rs[a[i]] = i;
        sum[a[i]] += 1;
    }
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i < n + 1; ++i){
        if (rs[a[i - 1]] != i - 1){
            dp[i] = dp[i - 1];
        } else{
            dp[rs[a[i - 1]] + 1] = max(dp[rs[a[i - 1]]], dp[ls[a[i - 1]]] + sum[a[i - 1]]);
        }
    }
    cout << dp.back() << endl;
    return 0;
}
