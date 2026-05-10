#include<iostream>
#include<vector>

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
    vector<int> a(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        if (a[i] == 1){
            cnt += 1;
        }
    }
    if (cnt != 0){
        cout << n - cnt;
        return 0;
    }
    for (int i = 1; i < n; ++i){
        if (gcd(a[i - 1], a[i]) == 1){
            cout << n;
            return 0;
        }
    }
    int minm = 1e9;
    for (int i = 1; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (j == i - 1 || j == i) continue;
            if (gcd(a[j], gcd(a[i], a[i - 1])) == 1){
                if (j > i){
                    minm = min(minm, 1 + j - i);
                } else{
                    minm = min(minm, i - 1 - j + 1);
                }
            }
        }
    }
    if (minm == 1e9){
        cout << -1;
    } else{
        cout << minm + n - 1;
    }
    return 0;
}
