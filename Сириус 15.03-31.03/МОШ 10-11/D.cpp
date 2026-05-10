#include<bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

__int128 e = 1;
mt19937 rnd(time(0));

double get(__int128 mask, vector<double> x, vector<int> c) {
    int n = (int)x.size();
    double now = 1;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
            now *= x[i];
            sum += c[i];
        }
    }
    return now - sum;
}

pair<int, int> solve(__int128 mask, vector<double> x, vector<int> c) {
    int n = x.size();
    int cnt = 0;
    int MAX = 2000000;
    double ans = get(mask, x, c);
    int maxm = mask;
    while (cnt < MAX) {
        __int128 i = rnd() % n;
        __int128 j = rnd() % n;
        __int128 new_mask = mask;
        for (int l = i; l <= j; ++l) {
            new_mask ^= (e << l);
        }
        double u = get(mask, x, c);
        double v = get(new_mask, x, c);
        if (u < v || (double)(rnd() % (int)1e9) / 1e9 < pow((double)MAX / (cnt * cnt), 1)) {
            mask = new_mask;
            if (v > ans) {
                ans = v;
                maxm = mask;
            }
        }
        cnt++;
    }
    return {ans, maxm};
}

signed main() {
    freopen("d2.txt", "r", stdin);
    freopen("d2ans4.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<double> x(n);
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
            x[i] = 1 + (x[i] / 100);
        }
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }
        double ans = 1;
        __int128 mask = 0;
        for (int i = 0; i < 5; ++i) {
            pair<double, int> tr = solve(mask, x, c);
            if (tr.first >= ans) {
                ans = tr.first;
                mask = tr.second;
            }
        }
        vector<int> rans;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                rans.push_back(i + 1);
            }
        }
        cout << rans.size() << endl;
        for (int i = 0; i < (int)rans.size(); ++i) {
            cout << rans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
