#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    int fl[2];
    int fl2[2];
    int go[A];
    Node() {
        fl[0] = 0;
        fl[1] = 0;
        fl2[0] = 0;
        fl2[1] = 0;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<int> get(string s) {
    vector<int> ans((int)s.size() / 2);
    vector<int> z((int)s.size());
    z[0] = 0;
    int l = 0, r = 1;
    for (int i = 1; i < (int)s.size(); ++i) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < (int)s.size() && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (r < z[i] + i) {
            l = i;
            r = i + z[i];
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i){
        if (z[i + (int)ans.size() + 1] + i + (int)ans.size() + 1 == (int)s.size()) {
            ans[i] = 1;
        }
    }
    return ans;
}

vector<Node> bor(1);

long long ans = 0;

void add(string s, vector<int> ch, int tp) {
    int v = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        int ch2 = c - 'a';
        if (bor[v].go[ch2] == -1) {
            bor.push_back(Node());
            bor[v].go[ch2] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch2];
        if (i == (int)s.size() - 1) {
            ans += bor[v].fl[tp ^ 1];
        } else {
            ans += bor[v].fl[tp ^ 1] * ch[i + 1];
            bor[v].fl2[tp] += ch[i + 1];
        }
    }
    bor[v].fl[tp] += 1;
    ans += bor[v].fl2[tp ^ 1];
}

void del(string s, vector<int> ch, int tp) {
    int v = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        int ch2 = c - 'a';
        if (bor[v].go[ch2] == -1) {
            bor.push_back(Node());
            bor[v].go[ch2] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch2];
        if (i == (int)s.size() - 1) {
            ans -= bor[v].fl[tp ^ 1];
        } else {
            ans -= bor[v].fl[tp ^ 1] * ch[i + 1];
            bor[v].fl2[tp] -= ch[i + 1];
        }
    }
    bor[v].fl[tp] -= 1;
    ans -= bor[v].fl2[tp ^ 1];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        int tp;
        string s;
        cin >> tp >> t >> s;
        if (tp == 2) {
            reverse(s.begin(), s.end());
        }
        string s2 = s;
        reverse(s2.begin(), s2.end());
        string s3 = s2 + '#' + s;
        vector<int> ch = get(s3);
        tp--;
        ch[0] = 0;
        if (t == '+') {
            add(s, ch, tp);
        } else {
            del(s, ch, tp);
        }
        cout << ans << endl;
    }
    return 0;
}
