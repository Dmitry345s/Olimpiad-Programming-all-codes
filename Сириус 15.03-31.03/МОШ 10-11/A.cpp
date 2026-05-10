#include<bits/stdc++.h>

#define int long long

using namespace std;

vector<int> get(long long a) {
    if (a == 1) {
        return {};
    }
    vector<int> ans;
    int i = 2;
    int x = a;
    while (i * i <= x) {
        if (x % i == 0) {
            ans.push_back(i);
            x /= i;
        } else {
            i++;
        }
    }
    if (x == 1) {
        return ans;
    }
    int y = sqrtl(x);
    if (y * y == x) {
        ans.push_back(y);
        ans.push_back(y);
    } else {
        ans.push_back(x);
    }
    return ans;
}

int solve(vector<int> a) {
    sort(a.begin(), a.end());
    if (a.size() < 2) {
        return -1;
    }
    int ans = 0;
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        //cout << i << " " << a[i] << " " << a[i + 1] << endl;
        ans += (a[i + 1] - a[i]) * (i + 1) * (a.size() - i - 1);
    }
    return ans;
}

mt19937 rnd(time(0));

int trytoget(vector<int> ans, int l, int r) {
    int k = solve(ans);
    int cnt = l;
    int MAX = r;
    int now = solve(ans);
    /*while (cnt < MAX) {
        if (ans.size() == 2) break;
        sort(ans.begin(), ans.end());
        /*int i = rnd() % (int)ans.size();
        vector<int> new_ans = ans;
        int p = new_ans[i];
        new_ans.erase(lower_bound(new_ans.begin(), new_ans.end(), p));
        int j = rnd() % (int)new_ans.size();
        int p2 = new_ans[j];
        new_ans.erase(lower_bound(new_ans.begin(), new_ans.end(), p2));
        new_ans.push_back(p * p2);
        int p = ans[0] * ans[1];
        vector<int> new_ans = ans;
        new_ans.erase(new_ans.begin());
        new_ans.erase(new_ans.begin());
        new_ans.push_back(p);
        int u = solve(new_ans);
        int v = solve(ans);
        if (u < v || (double)(rnd() % (int)1e9) / 1e9 < pow((double)(MAX) / (double)(cnt * cnt), 5)) {
            ans = new_ans;
            now = min(now, u);
        } else {
            break;
        }
    }*/
    while (ans.size() > 2) {
        sort(ans.begin(), ans.end());
        int p = ans[0] * ans[1];
        vector<int> new_ans = ans;
        new_ans.erase(new_ans.begin());
        new_ans.erase(new_ans.begin());
        new_ans.push_back(p);
        ans = new_ans;
        now = min(now, solve(ans));
    }
    return now;
}

signed main() {
    freopen("a2.txt", "r", stdin);
    freopen("a2ans.txt", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        vector<int> ans = get(a);
        /*for (int j = 0; j < (int)ans.size(); ++j) {
            cout << ans[j] << " ";
        }
        cout << endl;*/
        if (solve(ans) == -1) {
            cout << -1 << endl;
        } else {
            cout << min(trytoget(ans, 0, 1000), trytoget(ans, 100, 10000)) << endl;
        }
    }
    return 0;
}
