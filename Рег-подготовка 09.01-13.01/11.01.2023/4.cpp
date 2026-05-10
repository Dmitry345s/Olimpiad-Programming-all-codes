#include<iostream>
#include<vector>

using namespace std;

int main(){
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_){
        int n, m;
        cin >> n >> m;
        if (n >= m && n % m == 0){
            cout << n - 1 << endl;
            for (int i = 1; i < n; ++i){
                cout << i << " ";
            }
            cout << endl;
            continue;
        }
        if (m > n && m % n == 0){
            cout << m - 1 << endl;
            for (int i = 1; i < m; ++i){
                cout << -i << " ";
            }
            cout << endl;
            continue;
        }
        if (n == 2){
            cout << m << endl;
            for (int i = 0; i < (m - 1) / 2; ++i){
                cout << (m + n) / 2 << " " << -((m + n) / 2) - 1 << " ";
            }
            cout << (m + n) / 2 << endl;
            continue;
        }
        if (m == 2){
            cout << n << endl;
            for (int i = 0; i < (n - 1) / 2; ++i){
                cout << -((m + n) / 2) << " " << (m + n) / 2 + 1 << " ";
            }
            cout << -((m + n) / 2) << endl;
            continue;
        }
        cout << 0 << endl;
    }
}
