#include<iostream>
#include<vector>

using namespace std;

int i_search(int l, int r, int x, vector<int>& dp){
    int m = (l + r) / 2;
    if (l + 1 >= r){
        if (dp[l] > x){
            return l;
        }
        if (dp[r] > x){
            return r;
        }
        if (dp[r] == x){
            return r + 1;
        }
    }
    if (dp[m] > x){
        return i_search(l, m, x, dp);
    } else{
        return i_search(m, r, x, dp);
    }
}
int main(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    vector<int> dp(n + 1, 1e9);
    dp[0] = -1;
    for (int i = 0; i < k; ++i){
        if (i % 2 == 0){
            for (int l = 0; l < n; ++l){
                int j = i_search(0, dp.size() - 1, a[l], dp);
                if (dp[j - 1] < a[l] && a[l] < dp[j]){
                dp[j] = a[l];
                }
            }
        } else{
            for (int l = n - 1; l >= 0; --l){
                int j = i_search(0, dp.size() - 1, a[l], dp);
                if (dp[j - 1] < a[l] && a[l] < dp[j]){
                    dp[j] = a[l];
                }
            }
        }
    }
    int ans;
    for (int i = 1; i < n + 1; ++i){
        if (dp[i] != 1e9){
            ans = i;
        }
    }
    cout << ans << endl;
}
