#include<bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> to;
    int leaf;
    Node() {
        to.resize(26);
        for (int i = 0; i < 26; ++i) {
            to[i] = 0;
        }
        leaf = 0;
    }
};

vector<Node> bor = {Node()};

void add(string &s, int j) {
    int n = 0;
    for (int i = j; i < s.size(); ++i) {
        bor[n].leaf += 1;
        int c = s[i] - 'a';
        if (!bor[n].to[c]) {
            bor[n].to[c] = bor.size();
            bor.push_back(Node());
        }
        n = bor[n].to[c];
    }
    bor[n].leaf += 1;
}

vector<long long> cnt(1e4);
long long ans = 0;

void dfs(int v, int h) {
    ans += cnt[h] * bor[v].leaf;
    cnt[h] += bor[v].leaf;
    for (int i = 25; i >= 0; --i) {
        if (bor[v].to[i]) {
            dfs(bor[v].to[i], h + 1);
        }
    }
}

signed main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        add(s, i);
    }
    dfs(0, 0);
    cout << ans << endl;
    return 0;
}
