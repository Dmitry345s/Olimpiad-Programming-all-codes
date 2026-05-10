#include<iostream>
#include<vector>

using namespace std;

int siftUp(int i, vector<int>& c) {
    if (c[i / 2] < c[i]) {
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

pair<int, int> get_max(vector<int>& c) {
    int ans = c[1];
    swap(c[1], c.back());
    c.pop_back();
    int d;
    if (c.size() > 1) {
        d = siftDown(1, c);
    } else {
        d = 0;
    }
    return {d, ans};
}

int my_erase(int i, vector<int>& c) {
    int ans = c[i];
    swap(c[i], c.back());
    c.pop_back();
    int d = siftUp(i, c);
    int k = siftDown(d, c);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> c(1, 1e9 + 7);
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            if (c.size() == 1) {
                cout << -1 << endl;
                continue;
            }
            pair<int, int> maxm = get_max(c);
            cout << maxm.first << " " << maxm.second << endl;
        } else if (x == 2) {
            int p;
            cin >> p;
            if (c.size() == n + 1) {
                cout << -1 << endl;
                continue;
            }
            c.push_back(p);
            int d = siftUp(c.size() - 1, c);
            cout << d << endl;
        } else {
            int j;
            cin >> j;
            if (c.size() <= j || j <= 0) {
                cout << -1 << endl;
                continue;
            }
            cout << my_erase(j, c) << endl;
        }
    }
    for (int i = 1; i < c.size(); ++i) {
        cout << c[i] << " ";
    }
    return 0;
}
