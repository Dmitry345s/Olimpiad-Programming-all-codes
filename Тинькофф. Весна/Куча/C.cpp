#include<iostream>
#include<vector>

using namespace std;

int siftDown(int i, vector<int>& c) {
    if (i * 2 + 1 < c.size()) {
        int maxm = max(c[i * 2], c[i * 2 + 1]);
        if (maxm > c[i]) {
            if (c[i * 2] == maxm) {
                swap(c[i], c[i * 2]);
                return siftDown(i * 2, c);
            }
            swap(c[i], c[i * 2 + 1]);
            return siftDown(i * 2 + 1, c);
        }
    } else if (i * 2 < c.size()) {
        if (c[i * 2] > c[i]) {
            swap(c[i], c[i * 2]);
            return siftDown(i * 2, c);
        }
    }
    return i;
}

pair<int, int> get_max(vector<int>& c) {
    int ans = c[1];
    swap(c[1], c.back());
    c.pop_back();
    int d = siftDown(1, c);
    return {d, ans};
}

int main() {
    int n;
    cin >> n;
    vector<int> c(n + 1, 1e9 + 7);
    for (int i = 1; i < n + 1; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        pair<int, int> maxm = get_max(c);
        cout << maxm.first << " " << maxm.second << endl;
    }
    return 0;
}
