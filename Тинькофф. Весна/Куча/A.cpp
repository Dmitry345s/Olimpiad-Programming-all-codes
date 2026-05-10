#include<iostream>
#include<vector>

using namespace std;

int siftUp(int i, vector<int> & c) {
    if (c[i] > c[i / 2]) {
        swap(c[i], c[i / 2]);
        return siftUp(i / 2, c);
    }
    return i;
}

int main() {
    int n;
    cin >> n;
    vector<int> c(n + 1, 1e9 + 7);
    for (int i = 1; i < n + 1; ++i) {
        cin >> c[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int j, x;
        cin >> j >> x;
        c[j] += x;
        int d = siftUp(j, c);
        cout << d << endl;
    }
    for (int i = 1; i < n + 1; ++i) {
        cout << c[i] << " ";
    }
    return 0;
}
