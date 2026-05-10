#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main() {
    long long n;
    //cin >> n;
    //cout << (n - n % 4) / 3 + n % 4 / 3 << endl;
    vector<int> ans(2000);
    for (int i = 1; i < 2000; ++i) {
        int x = i, cnt = 0;
        while (x > 0) {
            cnt += x % 2;
            x = x >> 1;
        }
        ans[i + cnt] += 1;
    }
    int cnt2 = 0;
    for (int i = 1; i < ans.size(); ++i) {
        //cout << cnt2 << " ";
        if (ans[i] == 0) {
            int x = i;
            string k;
            while (x > 0) {
                int cnt = x % 2;
                x = x >> 1;
                k += char(cnt + int('0'));
            }
            reverse(k.begin(), k.end());
            cout << k << " ";
            cnt2 += 1;
        }
    }
    return 0;
}
