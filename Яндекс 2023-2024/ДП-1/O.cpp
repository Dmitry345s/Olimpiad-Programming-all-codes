#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n + 1);
    const int W = 6250001;
    bitset<W> bag, nbag, n2bag;
    int get[W];
    bag[0] = 1;
    get[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        nbag = (bag | (bag << a[i]));
        n2bag = (bag ^ nbag);
        for (int j = 0; j < W; j = n2bag._Find_next(j)) {
            get[j] = i;
        }
        bag = nbag;
    }
    if (!bag[w]) {
        cout << "NO" << endl;
        return 0;
    }
    int now = w;
    vector<int> ans;
    while (now != 0) {
        ans.push_back(get[now]);
        now -= a[get[now]];
    }
    cout << "YES" << endl;
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
