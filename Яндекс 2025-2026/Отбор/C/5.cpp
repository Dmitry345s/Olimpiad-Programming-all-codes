#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int x = n - (int)a.size();
    int now = 1;
    for (int i = 0; i < (int)a.size(); ++i) {
        //cout << i << " " << now << endl;
        while (i < (int)a.size() && now < a[i]) {
            if (x > 1) {
                x -= 2;
                now++;
            } else if (x == 1 && (int)a.size() - i >= 1) {
                x = 0;
                a.pop_back();
                now++;
            } else if ((int)a.size() - i >= 2) {
                a.pop_back();
                a.pop_back();
                now++;
            } else {
                break;
            }
        }
        if (i >= (int)a.size() || i < (int)a.size() && now < a[i]) {
            break;
        }
        now++;
    }
    now += x / 2;
    cout << now - 1 << endl;
    return 0;
}
