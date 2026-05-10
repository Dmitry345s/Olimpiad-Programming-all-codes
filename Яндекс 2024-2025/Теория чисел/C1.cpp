#include<bits/stdc++.h>

# define int long long
using namespace std;

vector<int> solve(int n) {
    vector<int> ans;
    int x = n;
    for (int i = 2; i * i <= x; ++i) {
        if (n % i != 0) continue;
        ans.push_back(i);
        while (n % i == 0) {
            n /= i;
        }
    }
    if (n > 1) {
        ans.push_back(n);
    }
    return ans;
}

int fpow(int a, int x, int p) {
    int ans = 1;
    while (x != 0) {
        if (x % 2 == 1) {
            ans = (1ll * ans * a) % p;
        }
        a = (1ll * a * a) % p;
        x /= 2;
    }
    return ans;
}

signed main() {
    int p;
    cin >> p;
    if (p == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> rans = solve(p - 1);
    vector<int> to_up;
    for (int i = 0; i < (int)rans.size(); ++i) {
        to_up.push_back((p - 1) / rans[i]);
    }
    int g = 1;
    for (int i = 2; i < p; ++i) {
        int flag = 1;
        for (auto u : to_up) {
            int x = fpow(i, u, p);
            if (x == 1) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            g = i;
            break;
        }
    }
    int gan = fpow(g, p - 2, p);
    vector<int> ans((p + 98) / 100);
    int now = 1, now2 = 1;
    for (int i = 0; i < p - 1; ++i) {
        now = (1ll * now * g) % p;
        now2 = (1ll * now2 * gan) % p;
        //cout << now << " " << now2 << endl;
        ans[(now - 1) / 100] = (ans[(now - 1) / 100] + now2) % p;
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
