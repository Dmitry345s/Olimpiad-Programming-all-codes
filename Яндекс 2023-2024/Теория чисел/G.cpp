#include<bits/stdc++.h>

using namespace std;

int MAX = 1e6 + 5;
vector<int> pr(MAX, 1);

void start() {
    pr[1] = 0;
    for (int i = 2; i * i < MAX; ++i) {
        if (pr[i]) {
            for (int j = i * i; j < MAX; j += i) {
                pr[j] = 0;
            }
        }
    }
}

signed main() {
    start();
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; ++i) {
        if (pr[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
