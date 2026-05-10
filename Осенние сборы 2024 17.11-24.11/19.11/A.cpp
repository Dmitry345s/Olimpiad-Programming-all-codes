#include<bits/stdc++.h>

using namespace std;

vector<string> ans;

vector<int> get(string & a) {
    vector<int> tans(26);
    for (int i = 0; i < (int)a.size(); ++i) {
        tans[a[i] - 'a']++;
    }
    return tans;
}

int tr(string & a, string & b) {
    vector<int> cnt = get(b);
    int sum = (int)b.size();
    int l = 0;
    int now = 0;
    int last = -1;
    string mans;
    int flag = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        l = 0;
        now = 0;
        while (l < 26 && (cnt[l] == 0 || l < (a[i] - 'a'))) {
            now += cnt[l];
            l++;
        }
        //cout << i << " " << l << " " << cnt[l] << endl;
        if (l == 26) {
            flag = -1;
            break;
        }
        now += cnt[l];
        //cout << "! " << sum << " " << now << endl;
        if (sum - now > 0) {
            last = i;
        }
        mans.push_back((char)(97 + l));
        cnt[l]--;
        sum--;
        if (l > (a[i] - 'a')) {
            flag = 1;
            break;
        }
    }
    //cout << mans << endl;
    if (flag != -1) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < cnt[i]; ++j) {
                mans.push_back((char)(i + 97));
            }
        }
        ans.push_back(mans);
        return 1;
    }
    if (last == -1) return 0;
    cnt = get(b);
    mans.clear();
    //cout << last << endl;
    for (int i = 0; i < last; ++i) {
        l = 0;
        while (l < 26 && (cnt[l] == 0 || l < (a[i] - 'a'))) {
            l++;
        }
        mans.push_back((char)(97 + l));
        cnt[l]--;
    }
    l = 0;
    while (l < 26 && (cnt[l] == 0 || l <= (a[last] - 'a'))) {
        l++;
    }
    mans.push_back((char)(97 + l));
    cnt[l]--;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            mans.push_back((char)(i + 97));
        }
    }
    if (mans < a) {
        return 0;
    }
    ans.push_back(mans);
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a[0].begin(), a[0].end());
    ans.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        int flag = tr(ans.back(), a[i]);
        if (!flag) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
