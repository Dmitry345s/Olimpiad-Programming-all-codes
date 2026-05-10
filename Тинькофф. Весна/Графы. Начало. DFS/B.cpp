#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int i, j;
    vector<int> deg(n, 0);
    for (int l = 0; l < m; ++l) {
        cin >> i >> j;
        deg[i - 1] += 1;
        deg[j - 1] += 1;
    }
    for (int i = 0; i < n; ++i) {
        cout << deg[i] << " ";
    }
    return 0;
}
