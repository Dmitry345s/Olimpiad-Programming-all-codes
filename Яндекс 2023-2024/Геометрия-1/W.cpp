#include<bits/stdc++.h>

using namespace std;

signed main() {
    long long h, l;
    cin >> h >> l;
    cout << setprecision(10) << (double)(h * h + l * l) / (2 * h) - h << endl;
    return 0;
}
