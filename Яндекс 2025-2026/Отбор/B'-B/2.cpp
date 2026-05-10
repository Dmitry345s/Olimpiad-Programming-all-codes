#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    multiset<int> q1;
    queue<int> q2;
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        if (t == "level") {
            while (!q2.empty()) {
                q1.insert(q2.front());
                q2.pop();
            }
        } else if (t == "talon") {
            int x;
            cin >> x;
            q2.push(x);
        } else {
            if (!q1.empty()) {
                cout << *q1.begin() << endl;
                q1.erase(q1.begin());
            } else {
                cout << q2.front() << endl;
                q2.pop();
            }
        }
    }
    return 0;
}
