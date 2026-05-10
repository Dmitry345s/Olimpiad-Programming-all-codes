#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long mod = 1e9 + 57;
int p = 31;

vector<long long> get_hash(string s) {
    vector<long long> pows(s.size() + 1);
    pows[1] = 1;
    for (int i = 2; i < int(pows.size()); ++i) {
        pows[i] = (pows[i - 1] * p) % mod;
    }
    vector<long long> h(s.size() + 1);
    h[0] = 0;
    for (int i = 1; i < int(h.size()); ++i) {
        h[i] = (h[i - 1] + (int(s[i - 1]) - 97 + 1) * pows[i]) % mod;
    }
    return h;
}

vector<long long> z_function(string s) {
    vector<long long> near_ans = get_hash(s);
    vector<long long> ans;
    int l = 0, r = 0;
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    ans.push_back(near_ans[n]);
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (z[i] + i < n && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        if (z[i] == n - i) {
            ans.push_back(near_ans[n - i]);
        }
    }
    return ans;
}
int main() {
    int n;
    cin >> n;
    vector<long long> ha;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        vector<long long> hashes = z_function(s);
        for (int j = 0; j < int(hashes.size()); ++j) {
            ha.push_back(hashes[j]);
        }
    }
    sort(ha.begin(), ha.end());
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        long long hash_s = get_hash(s).back();
        cout << (upper_bound(ha.begin(), ha.end(), hash_s) - lower_bound(ha.begin(), ha.end(), hash_s)) << endl;
    }
    return 0;

}
