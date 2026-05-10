#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> tree(800000, {200000, -200000, 0});

void update(int l, int r, int v, int x, int c){
    int m = (l + r) / 2;
    bool flag = false;
    if (l + 1 == r){
        tree[v][0] = x;
        tree[v][1] = x;
        tree[v][2] = 1;
        flag = true;
    }else if (c >= m){
        update(m, r, 2 * v + 1, x, c);
    } else{
        update(l, m, 2 * v, x, c);
    }
    if (!flag){
        tree[v][0] = min(tree[2 * v][0], tree[2 * v + 1][0]);
        tree[v][1] = max(tree[2 * v][1], tree[2 * v + 1][1]);
        tree[v][2] = max(max(tree[2 * v][2], tree[2 * v + 1][2]), tree[2 * v + 1][1] - tree[2 * v][0] + 1);
    }
}

vector<int> get_ans(int l, int r, int v, int x, int y){
    int m = (l + r) / 2;
    if (l == x && r == y){
        return tree[v];
    }
    if (y <= m && x >= l){
        return get_ans(l, m, 2 * v, x, y);
    }
    if (x >= m && y <= r){
        return get_ans(m, r, 2 * v + 1, x, y);
    }
    vector<int> f = get_ans(l, m, 2 * v, x, m), s = get_ans(m, r, 2 * v + 1, m, y);
    return {min(f[0], s[0]), max(f[1], s[1]), max(max(f[2], s[2]), s[1] - f[0] + 1)};
}

int main(){
    ios::sync_with_stdio();
    cout.tie(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int a;
    for (int i = 0; i < n; ++i){
        cin >> a;
        update(0, n, 1, a, i);
    }
    int l, r;
    for (int i = 0; i < m; ++i){
        cin >> l >> r;
        cout << get_ans(0, n, 1, l - 1, r)[2] << endl;
    }
    return 0;
}
