#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        sum += a[i];
    }
    if (n * q < 1e8){
        int t, l, r, x;
        for (int _ = 0; _ < q; ++_){
            cin >> t >> l >> r;
            if (t == 1){
                cin >> x;
                for (int i = l - 1; i <= r - 1; ++i){
                    a[i] = x;
                }
            } else{
                long long ans = 0;
                long long y = 0;
                for (int i = l - 1; i <= r - 1; ++i){
                    y = a[i] * (i - l + 2);
                    y %= 1000000007;
                    y *= (i - l + 2);
                    y %= 1000000007;
                    ans += y;
                    ans %= 1000000007;
                }
                cout << ans << endl;
            }
        }
    } else if (sum == n){
        int t, l, r;
        for (int _ = 0; _ < q; ++_){
            cin >> t >> l >> r;
            long long z = r - l + 1;
            long long temp = z * (z + 1) * (2 * z + 1);
            temp /= 6;
            temp %= 1000000007;
            cout << temp << endl;
        }
    }
    return 0;
}
