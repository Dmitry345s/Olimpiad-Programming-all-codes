#include<iostream>
#include<vector>
#include<string>
#include<set>

using namespace std;

long long mod = 1e9 + 7, mod2 = 1791791791;

long long gcd(long long a, long long b, long long & x, long long & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int main() {
    string t, s;
    cin >> t >> s;
    int n = s.size(), k = t.size();
    if (k > n) {
        cout << 0 << endl;
        return 0;
    }
    int p = 59;
    vector<long long> pows(n), pows2(n);
    pows[0] = 1;
    pows2[0] = 1;
    for (int i = 1; i < n; ++i) {
        pows[i] = (pows[i - 1] * p) % mod;
        pows2[i] = (pows2[i - 1] * p) % mod2;
    }
    vector<long long> h(k), h3(k);
    if (int(t[0]) >= 97) {
        h[0] = int(t[0]) - 70;
        h3[0] = h[0];
    } else {
        h[0] = int(t[0]) - 65 + 1;
        h3[0] = h[0];
    }
    for (int i = 1; i < k; ++i) {
        int c = int(t[i]);
        if (c >= 97) {
            h[i] = (h[i - 1] + (c - (97 - 27)) * pows[i]) % mod;
            h3[i] = (h3[i - 1] + (c - 70) * pows2[i]) % mod2;
        } else {
            h[i] = (h[i - 1] + (c - 65 + 1) * pows[i]) % mod;
            h3[i] = (h3[i - 1] + (c - 65 + 1) * pows2[i]) % mod2;
        }
    }
    set<long long> ts, ts2;
    for (int i = 0; i < k; ++i) {
        for (int j = 1; j < 53; ++j) {
            long long hash1 = (h[k - 1] - h[i] + mod) % mod, hash3 = (h3[k - 1] - h3[i] + mod2) % mod2;
            long long hash2 = 0, hash4 = 0;
            if (i > 0) {
                hash2 = h[i - 1];
                hash4 = h3[i - 1];
            }
            long long lhash = ((hash2 + (j * pows[i])) % mod + hash1) % mod, lhash2 = ((hash4 + (j * pows2[i])) % mod2 + hash3) % mod2;
            ts.insert(lhash);
            ts2.insert(lhash2);
        }
    }
    vector<long long> h2(n), h4(n);
    if (int(s[0]) >= 97) {
        h2[0] = int(s[0]) - 70;
        h4[0] = h2[0];
    } else {
        h2[0] = int(s[0]) - 65 + 1;
        h4[0] = h2[0];
    }
    for (int i = 1; i < n; ++i) {
        int c = int(s[i]);
        if (c >= 97) {
            h2[i] = (h2[i - 1] + (c - (97 - 27)) * pows[i]) % mod;
            h4[i] = (h4[i - 1] + (c - (97 - 27)) * pows2[i]) % mod2;
        } else {
            h2[i] = (h2[i - 1] + (c - 65 + 1) * pows[i]) % mod;
            h4[i] = (h4[i - 1] + (c - 65 + 1) * pows2[i]) % mod2;
        }
    }
    vector<int> ans;
    for (int i = 0; i < n - k + 1; ++i) {
        long long bhash = h2[i + k - 1], bhash2 = h4[i + k - 1];
        if (i > 0) {
            bhash -= h2[i - 1];
            bhash2 -= h4[i - 1];
        }
        bhash = (bhash + mod) % mod;
        bhash2 = (bhash2 + mod2) % mod2;
        long long x, y, x2, y2;
        long long d = gcd(pows[i], mod, x, y), d2 = gcd(pows2[i], mod2, x2, y2);
        x = (x % mod + mod) % mod;
        x2 = (x2 % mod2 + mod2) % mod2;
        if (ts.find((bhash * x) % mod) != ts.end() && ts2.find((bhash2 * x2) % mod2) != ts2.end()) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
