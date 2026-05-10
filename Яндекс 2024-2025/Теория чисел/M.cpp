#include<bits/stdc++.h>

# define int long long

using namespace std;

vector<int> simp, all;

void get(int m) {
    int x = m;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            all.push_back(i);
            if (i * i != x) {
                all.push_back(x / i);
            }
        }
        if (m % i == 0) {
            simp.push_back(i);
        }
        while (m % i == 0) {
            m /= i;
        }
    }
    if (m != 1) {
        simp.push_back(m);
    }
    sort(all.begin(), all.end());
    all.push_back(x);
}

signed main() {
    int n, m;
    cin >> n >> m;
    get(m);
    if (m == 1) {
        cout << n << endl;
        return 0;
    }
    vector<int> now((int)all.size());
    int ans = n;
    for (int i = (int)all.size() - 1; i >= 0; --i) {
        int del = n / all[i];
        //cout << all[i] << endl;
        for (int j = i + 1; j < (int)all.size(); ++j) {
            if (all[j] % all[i] == 0) {
                del -= now[j];
            }
        }
        //cout << del << endl;
        now[i] = del;
        ans -= del;
    }
    cout << ans << endl;
    return 0;
}
