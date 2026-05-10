#include<bits/stdc++.h>

using namespace std;

const int A = 2;

struct Node {
    int p, pr, sl, spl;
    int go[A];
    int fl;
    Node() {
        fl = 0;
        p = 0;
        pr = 0;
        sl = 0;
        spl = 0;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(string s) {
    int v = 0;
    for (auto c : s) {
        int ch = c - '0';
        if (bor[v].go[ch] == -1) {
            bor.push_back(Node());
            bor.back().pr = v;
            bor.back().p = ch;
            bor[v].go[ch] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch];
    }
    bor[v].fl = 1;
}

const int MAX = 3e5;
vector<vector<int>> g(MAX);
vector<int> used(MAX);

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].go[i] != -1) {
            q.push(bor[0].go[i]);
            g[0].push_back(bor[0].go[i]);
            continue;
        }
        bor[0].go[i] = 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (bor[v].pr == 0) {
            bor[v].sl = 0;
        } else {
            bor[v].sl = bor[bor[bor[v].pr].sl].go[bor[v].p];
        }
        if (bor[bor[v].sl].fl) {
            bor[v].spl = bor[v].sl;
        } else {
            bor[v].spl = bor[bor[v].sl].spl;
        }
        //cout << v << " " << bor[v].sl << " " << bor[v].spl << endl;
        if (bor[v].spl != 0 || bor[v].fl) {
            used[v] = 1;
        }
        for (int i = 0; i < A; ++i) {
            if (bor[v].go[i] != -1) {
                q.push(bor[v].go[i]);
            } else {
                bor[v].go[i] = bor[bor[v].sl].go[i];
            }
            g[v].push_back(bor[v].go[i]);
            //cout << v << " " << bor[v].go[i] << endl;
        }
    }
}

bool flag = 0;

void dfs(int v = 0, int p = 0) {
    used[v] = -1;
    for (int to : g[v]) {
        if (used[to] == 1) continue;
        if (used[to] == -1) {
            flag = 1;
            return;
        }
        dfs(to, v);
    }
    used[v] = 1;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    bfs();
    dfs();
    //cout << flag << endl;
    if (flag) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }
    return 0;
}
