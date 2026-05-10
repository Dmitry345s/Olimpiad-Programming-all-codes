#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;
int start[MAX], classid[MAX], ans[MAX], mem[MAX], cnt[MAX], pref[MAX], lcp[MAX];
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
    int m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    s.push_back(0);
    n += 1;
    vector<pair<int, int>> a;
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
    lcp[n] = -1;
    vector<pair<int, int>> st;
    st.push_back({-1, -1});
    long long ans = 0;
    int to_ans = 0;
    int to_ans2 = 0;
    for (int i = 0; i <= n; ++i) {
        //cout << ans << endl;
        while (st.back().first > lcp[i]) {
            //cout << i << " " << st.back().first << " " << st.back().second << endl;
            long long val = st.back().first;
            //st.pop_back();
            int len = i - st[(int)st.size() - 2].second;
            if (ans < val * len) {
                ans = val * len;
                to_ans = st.back().second;
                to_ans2 = val;
            }
            st.pop_back();
        }
        st.push_back({lcp[i], i});
    }
    //cout << to_ans << endl;
    if (n - 1 > ans) {
        cout << n - 1 << endl;
        cout << n - 1 << endl;
        for (int i = 0; i < n - 1; ++i) {
            cout << s[i] << " ";
        }
        cout << endl;
        return 0;
    }
    vector<int> rans;
    for (int i = start[to_ans]; i < start[to_ans] + to_ans2; ++i) {
        rans.push_back(s[i]);
    }
    cout << ans << endl;
    cout << (int)rans.size() << endl;
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i] << " ";
    }
    cout << endl;
    return 0;
}
