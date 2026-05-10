#include<bits/stdc++.h>

using namespace std;

signed main() {
    freopen("sufflcp.in", "r", stdin);
    freopen("sufflcp.out", "w", stdout);
    int n;
    cin >> n;
    string s;
    cin >> s;
    s.push_back(char((int)'a' - 1));
    vector<int> start(n);
    vector<int> classid(n);
    for (int i = 0; i < n; ++i) {
        cin >> start[i];
        start[i]--;
        classid[start[i]] = i;
    }
    int k = 0;
    vector<int> lcp(n);
    for (int i = 0; i < n; ++i) {
        int j = classid[i];
        if (j == 0) {
            lcp[0] = 0;
            continue;
        }
        int p = start[j - 1];
        while (s[i + k] == s[p + k]) k++;
        lcp[j] = k;
        k = max(k - 1, 0);
    }
    for (int i = 1; i < n; ++i) {
        cout << lcp[i] << " ";
    }
    cout << endl;
    return 0;
}
