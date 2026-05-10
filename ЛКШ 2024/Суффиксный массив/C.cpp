#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 2;
int start[MAX], classid[MAX], ans[MAX], cnt[MAX], mem[MAX], pref[MAX], lcp[MAX];
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
        pref[i] = pref[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        ans[pref[classid[start[i]]]++] = start[i];
    }
}

signed main() {
    string s;
    cin >> s;
    s.push_back(char((int)'a' - 1));
    n = s.size();
    vector<pair<char, int>> a;
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
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int j = classid[i];
        if (j == 0) {
            lcp[j] = 0;
            continue;
        }
        int p = start[j - 1];
        while (s[i + k] == s[p + k]) k++;
        lcp[j] = k;
        k = max(k - 1, 0);
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += n - start[i] - lcp[i] - 1;
    }
    cout << ans << endl;
}
