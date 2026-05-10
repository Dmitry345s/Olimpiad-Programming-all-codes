#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
    vector<int> s(n);
    vector<int> rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        rs[p[i]] = s[i];
    }
    vector<int> nperm(n);
    for (int i = 0; i < n; ++i) nperm[i] = i;
    int ans = 0;
    do {
        int now = 0;
        for (int i = 0; i < n; ++i) {
            int fl = 1;
            if (i - 1 >= 0 && nperm[i] < nperm[i - 1]) fl = 0;
            if (i + 1 < n && nperm[i] < nperm[i + 1]) fl = 0;
            now += fl * rs[nperm[i]];
        }
        if (now <= k) ans++;
    } while (next_permutation(nperm.begin(), nperm.end()));
    cout << ans << endl;
    return 0;
}
