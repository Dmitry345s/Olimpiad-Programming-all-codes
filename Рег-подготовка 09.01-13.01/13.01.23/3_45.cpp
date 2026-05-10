#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    int l, r;
    for (int i = 0; i < m; ++i){
        cin >> l >> r;
        int ans = 0;
        int minm = a[l - 1];
        int maxm = a[l - 1];
        for (int j = l - 1; j < r; ++j){
            if (a[j] < minm){
                minm = a[j];
                maxm = a[j];
            }
            maxm = max(maxm, a[j]);
            ans = max(ans, maxm - minm + 1);
        }
        cout << ans << endl;
    }
}
