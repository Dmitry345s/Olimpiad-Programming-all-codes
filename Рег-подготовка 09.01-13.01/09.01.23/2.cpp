#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int gcd(int a, int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main(){
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long minm = 1e18;
    for (int i = 0; i < min(1000, n); ++i){
        for (int j = i + 1; j < min(1000, n); ++j){
            minm = min(minm, a[i] * a[j] / gcd(a[i], a[j]));
        }
    }
    cout << minm << endl;
}
