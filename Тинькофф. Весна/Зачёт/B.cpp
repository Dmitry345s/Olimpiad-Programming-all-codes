#include<iostream>
#include<vector>
#include<string>

using namespace std;

int k = 5000;
vector<pair<int, vector<int>>> b(500000 / k);

void update(int i, char c, char p) {
    int s = i / k;
    if (b[s].second[int(p) - 97] == 1) {
        b[s].first -= 1;
    }
    b[s].second[int(p) - 97] -= 1;
    if (b[s].second[int(c) - 97] == 0) {
        b[s].first += 1;
    }
    b[s].second[int(c) - 97] += 1;
}

int get_ans(int l, int r, string& t) {
    int f = l / k, s = r / k;
    vector<int> v(26);
    if (f == s) {
        int ans = 0;
        for (int i = l; i <= r; ++i) {
            v[int(t[i]) - 97] += 1;
            if (v[int(t[i]) - 97] == 1) {
                ans += 1;
            }
        }
        return ans;
    }
    int cnt = 0;
    for (int i = f + 1; i < s; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (v[j] == 0 && b[i].second[j] != 0) {
                cnt += 1;
            }
            v[j] += b[i].second[j];
        }
    }
    for (int i = l; i < (f + 1) * k; ++i) {
        v[int(t[i]) - 97] += 1;
        if (v[int(t[i]) - 97] == 1) {
            cnt += 1;
        }
    }
    for (int i = r; i >= s * k; --i) {
        v[int(t[i]) - 97] += 1;
        if (v[int(t[i]) - 97] == 1) {
            cnt += 1;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int t = (n + k - 1) / k;
    for (int i = 0; i < t; ++i) {
        vector<int> v(26);
        int cnt = 0;
        for (int j = i * k; j < min(i * k + k, n); ++j) {
            v[int(s[j]) - 97] += 1;
            if (v[int(s[j]) - 97] == 1) {
                cnt += 1;
            }
        }
        b[i].first = cnt;
        b[i].second = v;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int now, l, r;
        char c;
        cin >> now;
        if (now == 1) {
            cin >> l >> c;
            update(l - 1, c, s[l - 1]);
            s[l - 1] = c;
        } else {
            cin >> l >> r;
            cout << get_ans(l - 1, r - 1, s) << endl;
        }
    }
    return 0;
}
