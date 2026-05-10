#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 130;
int tree[MAX][MAX][MAX];

void update(int x, int y, int z, int d, int n) {
    for (int i = x; i < MAX; i = ((i + 1) | i)) {
        for (int j = y; j < MAX; j = ((j + 1) | j)) {
            for (int k = z; k < MAX; k = ((k + 1) | k)) {
                tree[i][j][k] += d;
            }
        }
    }
}

int get(int x, int y, int z) {
    int ans = 0;
    for (int i = x; i >= 0; i = ((i + 1) & i) - 1) {
        for (int j = y; j >= 0; j = ((j + 1) & j) - 1) {
            for (int k = z; k >= 0; k = ((k + 1) & k) - 1) {
                ans += tree[i][j][k];
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    while (true) {
        int t;
        cin >> t;
        if (t == 3) return 0;
        if (t == 1) {
            int x, y, z, v;
            cin >> x >> y >> z >> v;
            ++x; ++y; ++z;
            update(x, y, z, v, n);
        } else {
            int x, y, z, x2, y2, z2;
            cin >> x2 >> y2 >> z2 >> x >> y >> z;
            ++x; ++y; ++z;
            int plu = - get(x2, y, z) - get(x, y2, z) - get(x, y, z2) - get(x2, y2, z2);
            cout << get(x, y, z) + get(x, y2, z2) + get(x2, y, z2) + get(x2, y2, z) + plu << endl;
        }
    }
    return 0;
}
