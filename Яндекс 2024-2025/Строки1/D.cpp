#include<bits/stdc++.h>

using namespace std;

const int SZ = 30;

struct Node {
    int go[2];
    int cnt;
    int fl;
    Node() {
        go[0] = -1;
        go[1] = -1;
        cnt = 0;
        fl = 0;
    }
};

vector<Node> bor(1);

void add(int x) {
    int v = 0;
    for (int i = SZ; i >= 0; --i) {
        int c = ((x >> i) & 1);
        if (bor[v].go[c] == -1) {
            bor[v].go[c] = (int)bor.size();
            bor.push_back(Node());
        }
        bor[v].cnt++;
        v = bor[v].go[c];
    }
    bor[v].cnt++;
    bor[v].fl++;
}

void del(int x) {
    int v = 0;
    for (int i = SZ; i >= 0; --i) {
        int c = ((x >> i) & 1);
        bor[v].cnt--;
        v = bor[v].go[c];
    }
    bor[v].cnt--;
    bor[v].fl--;
}

int get(int x) {
    int v = 0;
    int y = 0;
    for (int i = SZ; i >= 0; --i) {
        int c = (((x >> i) & 1) ^ 1);
        if (bor[v].go[c] == -1 || bor[bor[v].go[c]].cnt == 0) {
            v = bor[v].go[c ^ 1];
            y = (y << 1) + (c ^ 1);
        } else {
            v = bor[v].go[c];
            y = (y << 1) + c;
        }
    }
    return y;
}

signed main() {
    int n;
    cin >> n;
    add(0);
    for (int i = 0; i < n; ++i) {
        char t;
        int x;
        cin >> t >> x;
        if (t == '+') {
            add(x);
        } else if (t == '-') {
            del(x);
        } else {
            cout << (get(x) ^ x) << endl;
        }
    }
    return 0;
}
