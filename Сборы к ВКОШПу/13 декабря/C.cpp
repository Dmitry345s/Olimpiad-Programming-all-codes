#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    int ns, nb, l, cur_ans;
    cin >> ns >> nb >> l;
    cur_ans = nb * l * l * l + ((ns + l * l - 1) / (l * l)) * (l * l);
    for (int cur_v = nb * l * l * l + ns; cur_v < cur_ans; cur_v++) {
        vector<int> cur_div = {};
        for (int small_div = 1; small_div * small_div <= cur_v; small_div++) {
            if (cur_v % small_div == 0) {
                cur_div.push_back(small_div);
            }
        }
        bool is_ans = false;
        for (auto div1 : cur_div) {
            for (auto div2 : cur_div) {
                if ((cur_v / div1) % div2 != 0) continue;
                if ((div1 / l) * (div2 / l) * ((cur_v / div1 / div2) / l) >= nb) {
                    is_ans = true;
                    break;
                }
            }
            if (is_ans) {
                break;
            }
        }
        if (is_ans) {
            cur_ans = cur_v;
            break;
        }
    }
    cout << cur_ans << endl;
}
