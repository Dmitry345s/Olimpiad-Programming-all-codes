#include<iostream>
#include<vector>

using namespace std;

struct for_graph{
    int v, to, len;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<for_graph> g(m);
    for (int l = 0; l < m; ++l) {
        int a, b;
        cin >> a >> b >> g[l].len;
        g[l].v = a - 1;
        g[l].to = b - 1;
    }
    int MAX = 30000;
    vector<int> d(n, MAX);
    d[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            if (d[g[j].v] < MAX) {
                d[g[j].to] = min(d[g[j].to], d[g[j].v] + g[j].len);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    return 0;
}
