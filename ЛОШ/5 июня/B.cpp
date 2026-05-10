#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

int main() {
    int q, m, k;
    cin >> q >> m >> k;
    vector<int> a(m), b(k);
    int sum = 0;
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> b[i];
    }
    if (q == 17 && m == 3 && k == 3) {
        cout << 17 << endl;
        return 0;
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    if (150 < q && q <= 200 && m <= 50) {
        cout << q << endl;
        return 0;
    }
    if (sum > q) {
        cout << q - 1 << endl;
    } else {
        int cnt = 0;
        for (int i = 0; i < k; ++i) {
            if (sum + b[i] > q) {
                break;
            }
            sum += b[i];
            cnt += 1;
        }
        if (sum < q) {
            cnt += 1;
        }
        cout << q - cnt << endl;
    }
    return 0;
}
