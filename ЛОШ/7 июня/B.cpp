#include<iostream>
#include<vector>
#include<map>

using namespace std;

long long mod = 1e9 + 7;

map<int, int> mp;

void factor (int k) {
    int i = 1;
    while (i * i <= k) {
        if (k % i == 0) {
            mp[i] = 0;
            mp[k / i] = 0;
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n + 1, vector<int> (n + 1, -1));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            cin >> a[i][j];
        }
    }
    return 0;
}
