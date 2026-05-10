#include<bits/stdc++.h>

#define int long long

using namespace std;

int cnt = 0;

vector<int> quick_sort(vector<int> a) {
    if ((int)a.size() <= 1) return a;
    vector<int> ls, gr;
    int del = a[0];
    for (int i = 1; i < (int)a.size(); ++i) {
        cnt++;
        if (a[i] < del) {
            ls.push_back(a[i]);
        } else {
            gr.push_back(a[i]);
        }
    }
    vector<int> ans = quick_sort(ls), gr2 = quick_sort(gr);
    ans.push_back(del);
    for (int i = 0; i < (int)gr2.size(); ++i) {
        ans.push_back(gr2[i]);
    }
    return ans;
}

int cnt2 = 0;
const int INF = 1e5;

void insertion_sort(int n, vector<int> a) {
    a.insert(a.begin(), -INF);
    for (int i = 2; i < n + 1; ++i) {
        int j = i;
        cnt2++;
        while (a[j - 1] > a[j]) {
            swap(a[j - 1], a[j]);
            j = j - 1;
            cnt2++;
        }
    }
}

const int MOD = 1234567;

signed main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    if (x >= 1) {
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            ans *= (i + 1);
            ans %= MOD;
        }
        cout << ans << endl;
        return 0;
    }
    if (n > 12) return 0;
    int ans = 0;
    do {
        cnt = 0;
        vector<int> b = quick_sort(a);
        cnt2 = 0;
        insertion_sort(n, a);
        if (cnt2 <= 3 * n - 2) {
            ans++;
            continue;
        }
        //cout << cnt << " " << cnt2 << endl;
        if (cnt2 <= cnt * x) {
            ans++;
        }
    } while (next_permutation(a.begin(), a.end()));
    cout << ans << endl;
    return 0;
}
