#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e7;
int ch[MAX];
vector<int> pr;

void sieve() {
    for (int i = 2; i < MAX; ++i) {
        if (ch[i] == 0) {
            pr.push_back(i);
            for (int j = 1ll * i * i; j < MAX; j += i) {
                ch[j] = i;
            }
        }
    }
}

signed main() {
    sieve();
    //cout << (int)pr.size() << endl;
    int n;
    cin >> n;
    int x = n;
    int i = 2;
    int ch = 0;
    while (i * i <= n) {
        while (x % i == 0) {
            ch ^= lower_bound(pr.begin(), pr.end(), i) - pr.begin() + 1;
            x /= i;
        }
        i++;
    }
    if (x != 1) {
        int y = lower_bound(pr.begin(), pr.end(), i) - pr.begin() + 1;
        if (y == (int)pr.size()) {
            ch = 1;
        } else {
            ch ^= y;
        }
    }
    if (ch == 0) {
        cout << "Vasya" << endl;
    } else {
        cout << "David" << endl;
    }
    return 0;
}
