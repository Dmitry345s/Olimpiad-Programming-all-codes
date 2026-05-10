#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<pair<int, int>> b(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        b[i] = {a[i] - i, i};
    }
    int l, r, x;
    sort(b.begin(), b.end());
    for (int i = 0; i < m; ++i){
        cin >> l >> r >> x;
        l -= 1;
        r -= 1;
        pair<int, int> f = {x - l, r}, s = {x - l, l};
        cout << upper_bound(b.begin(), b.end(), f) - lower_bound(b.begin(), b.end(), s) << endl;
    }
    return 0;
}
