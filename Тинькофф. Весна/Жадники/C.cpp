#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<long long> s;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        s.insert(x);
    }
    long long ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        long long q = *s.begin();
        s.erase(s.begin());
        long long q2 = *s.begin();
        s.erase(s.begin());
        long long y = q + q2;
        ans += y;
        s.insert(y);
    }
    cout << ans << endl;
}
