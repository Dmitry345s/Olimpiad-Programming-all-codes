#include<bits/stdc++.h>
#define int long long

using namespace std;

int MAX = 1e6;
vector<int> ch(MAX, 1), ch2(MAX, 1);

int get(int id, vector<int> & mnext, int n) {
    if (mnext[id] == n || mnext[id] == -1 || ch[mnext[id]]) {
        return mnext[id];
    }
    return mnext[id] = get(mnext[id], mnext, n);
}

int get2(int id, vector<int> & mnext, int n) {
    if (mnext[id] == n || mnext[id] == -1 || ch2[mnext[id]]) {
        return mnext[id];
    }
    return mnext[id] = get2(mnext[id], mnext, n);
}

mt19937 rnd(time(0));

signed main() {
    //cout << rnd() % 2 + 1 << " " << rnd() % 2 * 2 + 1 << endl;
    int n, k;
    cin >> n >> k;
    vector<int> ins = {-1};
    string s;
    for (int i = 0; i < n; ++i) {
        char p;
        cin >> p;
        if (p == 'w') {
            ins.push_back(i);
        }
        s += p;
    }
    ins.push_back(n);
    vector<int> mnext(n), prev(n), mnext2(ins.size()), prev2(ins.size());
    for (int i = 0; i < n; ++i) {
        mnext[i] = i + 1;
        prev[i] = i - 1;
    }
    for (int i = 0; i < ins.size(); ++i) {
        mnext2[i] = i + 1;
        prev2[i] = i - 1;
    }
    set<pair<int, int>> q;
    vector<int> d(ins.size());
    for (int i = 1; i < ins.size() - 1; ++i) {
        q.insert({-(ins[i + 1] - ins[i - 1] - 1), i});
        d[i] = ins[i + 1] - ins[i - 1] - 1;
    }
    vector<vector<int>> ans(n / (k + 1));
    for (int i = 0; i < ans.size(); ++i) {
        int id = q.begin()->second;
        ch2[id] = 0;
        ch[ins[id]] = 0;
        q.erase(q.begin());
        int now = ins[id];
        int cnt = 0;
        while((now != -1 && s[now] != 'w' || cnt == 0) && cnt <= k) {
            cnt++;
            ans[i].push_back(now);
            ch[now] = 0;
            now = get(now, prev, n);
        }
        now = get(ins[id], mnext, n);
        while((now != n && s[now] != 'w' || cnt == 0) && cnt <= k) {
            cnt++;
            ans[i].push_back(now);
            ch[now] = 0;
            now = get(now, mnext, n);
        }
        int next = get2(id, mnext2, ins.size());
        int pref = get2(id, prev2, ins.size());
        if (next != ins.size() - 1) {
            q.erase({-d[next], next});
            int next2 = get2(next, mnext2, ins.size());
            d[next] = (ins[next2] - ins[pref] - 1 - (k + 1) * (next2 - pref - 2));
            q.insert({-d[next], next});
        }
        if (pref != 0) {
            q.erase({-d[pref], pref});
            int pref2 = get2(pref, prev2, ins.size());
            d[pref] = (ins[next] - ins[pref2] - 1 - (k + 1) * (next - pref2 - 2));
            q.insert({-d[pref], pref});
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        for (int p : ans[i]) {
            cout << p + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
