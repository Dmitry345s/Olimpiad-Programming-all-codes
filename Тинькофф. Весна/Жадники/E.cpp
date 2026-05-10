#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, k, s;
    cin >> n >> k >> s;
    vector<int> dist(s);
    bool flag = true;
    for (int i = 0; i < s; ++i) {
        cin >> dist[i];
        if (i != 0 && dist[i] - dist[i - 1] > k || i == 0 && dist[i] > k) {
            flag = false;
        }
    }
    if (flag) {
        cout << (n + (k - 1)) / k - 1 << endl;
    } else {
        cout << -1 << endl;
    }
}
