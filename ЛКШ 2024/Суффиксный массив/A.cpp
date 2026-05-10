#include<bits/stdc++.h>

using namespace std;

const int MAX = 4e5 + 5;

int start[MAX], classid[MAX], ans[MAX], pref[MAX], cnt[MAX], mem[MAX];
int n;

int mod(int x) {
    if (x < 0) return x + n;
    if (x >= n) return x - n;
    return x;
}

void count_sort() {
    fill(cnt, cnt + n, 0);
    for (int i = 0; i < n; ++i) {
        cnt[classid[start[i]]]++;
    }
    pref[0] = 0;
    for (int i = 1; i < n; ++i) {
        //cout << cnt[i - 1] << " ";
        pref[i] = pref[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        ans[pref[classid[start[i]]]++] = start[i];
    }
}

signed main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    string s;
    cin >> s;
    s.push_back(char((int)'a' - 1));
    n = s.size();
    vector<pair<char, int>> a;
    //cout << s << endl;
    for (int i = 0; i < n; ++i) {
        a.push_back({s[i], i});
    }
    sort(a.begin(), a.end());
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        start[i] = a[i].second;
        classid[start[i]] = cnt;
        if (i < n - 1 && a[i].first != a[i + 1].first) cnt++;
    }
    for (int i = 0; i < n; ++i) {
        //cout << start[i] << " " << classid[start[i]] << endl;
    }
    int now = 0;
    while ((1 << now) < n) {
        for (int i = 0; i < n; ++i) {
            start[i] = mod(start[i] - (1 << now));
        }
        count_sort();
        for (int i = 0; i < n; ++i) {
            start[i] = ans[i];
            mem[i] = classid[i];
        }
        classid[start[0]] = 0;
        for (int i = 1; i < n; ++i) {
            classid[start[i]] = classid[start[i - 1]];
            if (pair<int, int>{mem[start[i]], mem[mod(start[i] + (1 << now))]} != pair<int, int>{mem[start[i - 1]], mem[mod(start[i - 1] + (1 << now))]}) {
                classid[start[i]]++;
            }
        }
        now++;
    }
    for (int i = 1; i < n; ++i) {
        cout << start[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
