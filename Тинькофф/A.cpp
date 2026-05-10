#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

bool check(vector<vector<double>>& a, double ans, double x){
    double cnt1 = 0, cnt2 = x * ans;
    int i = 0;
    while (i < a.size() && a[i][0] < ans){
        cnt1 += a[i][2] * ans;
        cnt2 += a[i][1];
        i += 1;
    }
    if (cnt1 - cnt2 > 0){
        return false;
    } else{
        return true;
    }
}

double i_search(double l, double r, vector<vector<double>>& a, double x){
    double m = (l + r) / 2;
    bool ans = check(a, m, x);
    if (l + 0.00001 >= r){
        return m;
    }else if(ans){
        return i_search(m, r, a, x);
    } else{
        return i_search(l, m, a, x);
    }
}

int main(){
    int n;
    double x;
    cin >> n >> x;
    vector<vector<double>> a(n, vector<double> (3));
    for (int i = 0; i < n; ++i){
        cin >> a[i][2] >> a[i][1];
        a[i][0] = a[i][1] / a[i][2];
    }
    sort(a.begin(), a.end());
    if (check(a, a.back()[0] + 1e13, x)){
        cout << -1;
    } else{
        cout << round(i_search(0, 1e18, a, x) * 1000000) / 1000000;
    }
    return 0;
}
