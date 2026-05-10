#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
using ull = unsigned long long;

const int A = 26;
const int p = 43;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<pair<ull, int>>> all_hashes(n);
    for (int i = 0; i < n; i++) {
        vector<int> new_ind(A, -1);
        int cur_ind = 1;
        ull cur_hash = 0;
        for (int j = i; j < n; j++) {
            cur_hash *= p;
            if (new_ind[s[j] - 'a'] == -1) {
                new_ind[s[j] - 'a'] = cur_ind++;
            }
            cur_hash += new_ind[s[j] - 'a'];
            all_hashes[j - i].push_back({cur_hash, i});
        }
    }
    int ans_len = 0;
    int ans_cnt = 0;
    int ans_ind = 0;
    for (int len = 0; len < n; len++) {
        sort(all(all_hashes[len]));
        int biggest_cnt = -1;
        int biggest_ind = -1;
        int cur_cnt = 1;
        int cur_ind = all_hashes[len][0].second;
        for (int i = 1; i < (int)all_hashes[len].size(); i++) {
            if (all_hashes[len][i].first == all_hashes[len][i - 1].first) {
                cur_cnt++;
                continue;
            } else {
                if (cur_cnt > biggest_cnt) {
                    biggest_cnt = cur_cnt;
                    biggest_ind = cur_ind;
                }
                cur_cnt = 1;
                cur_ind = all_hashes[len][i].second;
            }
        }
        if (cur_cnt > biggest_cnt) {
            biggest_cnt = cur_cnt;
            biggest_ind = cur_ind;
        }
//        cout << len + 1 << " " << biggest_cnt << endl;
        if ((len + 1) * biggest_cnt > ans_len * ans_cnt) {
            ans_len = len + 1;
            ans_cnt = biggest_cnt;
            ans_ind = biggest_ind;
        }
    }
//    cout << ans_cnt << " " << ans_len << endl;
    for (int i = ans_ind; i < ans_ind + ans_len; i++) {
        cout << s[i];
    }
    cout << endl;
}
