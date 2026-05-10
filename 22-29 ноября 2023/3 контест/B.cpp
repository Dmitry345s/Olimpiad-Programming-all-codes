#include<bits/stdc++.h>

using namespace std;

void mg(int n, vector<int> & get) {
    int i = 1;
    while (i * i < n) {
        if (n % i == 0) {
            get.push_back(n / i);
            get.push_back(i);
        }
        i++;
    }
    if (i * i == n) {
        get.push_back(i);
    }
    sort(get.begin(), get.end());
}

vector<int> a;
map<int, vector<int>> mp;

vector<int> rg(int n, int st) {
    if (n == 1) {
        mp[1] = {0};
        return {0};
    }
    vector<int> ans;
    for (int i = st; i < a.size(); ++i) {
        if (n % a[i] == 0) {
            vector<int> b;
            if (mp.find(n / a[i]) != mp.end()) {
                b = mp[n / a[i]];
            } else {
                b = rg(n / a[i], 1);
            }
            for (int j = 0; j < b.size(); ++j) {
                ans.push_back(b[j] + a[i] - 1);
            }
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    if (ans.size() == 0) {
        ans.push_back(n - 1);
    }
    /*cout << n << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;*/
    mp[n] = ans;
    return ans;
}

signed main() {
    int n;
    cin >> n;
    mg(n, a);
    vector<int> ans = rg(n, 1);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
}
