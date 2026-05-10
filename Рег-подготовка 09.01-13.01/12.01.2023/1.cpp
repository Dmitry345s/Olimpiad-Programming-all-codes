#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    vector<pair<int, int>> ans(3 * 100000 + 1, {-1, 1000000});
    for (int i = 0; i < n; ++i){
        if (ans[a[i]].first != -1){
            ans[a[i]].second = min(ans[a[i]].second, i - ans[a[i]].first);
            ans[a[i]].first = i;
        } else{
            ans[a[i]].first = i;
        }
    }
    int minm = 1000000;
    for (int i = 0; i < ans.size(); ++i){
        minm = min(minm, ans[i].second);
    }
    if (minm == 1000000){
        cout << -1 << endl;
    } else{
        cout << n - minm << endl;
    }
    return 0;
}
