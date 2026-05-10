#include<iostream>
#include<vector>

using namespace std;

int mod = 1e9 + 7;

int deg(int a, long long n){
    if (n == 0){
        return 1;
    }
    if (n % 2 == 0){
        long long x = deg(a, n / 2) % mod;
        return (x * x) % mod;
    } else{
        return (deg(a, n - 1) * a) % mod;
    }
}

int main(){
    long long n, m;
    int k;
    cin >> n >> m >> k;
    if (k == -1 && n % 2 != m % 2){
        cout << 0 << '\n';
    } else{
        int ans = deg(deg(2, n - 1), m - 1);
        cout << ans << '\n';
    }
    return 0;
}
