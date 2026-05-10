#include<iostream>
#include<vector>

using namespace std;

int siftUp(int i, vector<int>& c) {
    if (c[i] > c[i / 2]) {
        swap(c[i], c[i / 2]);
        return siftUp(i / 2, c);
    }
    return i;
}

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

int get_max(vector<int>& c) {
    int ans = c[1];
    swap(c[1], c.back());
    c.pop_back();
    int d = siftDown(1, c);
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> c(1, 1e9 + 7);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        c.push_back(x);
        int k = siftUp(c.size() - 1, c);
    }
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = get_max(c);
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
}
