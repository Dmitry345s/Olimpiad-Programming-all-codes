#include<bits/stdc++.h>
#include"toxic.h"

using namespace std;

void determine_type(int n) {
    vector<int> ch(n);
    for (int i = 0; i < n - 1; ++i) {
        vector<int> now = query_machine(vector<int>{i, i, i + 1, i + 1});
        if ((int)now.size() == 1) {
            ch[i + 1] = ch[i];
        } else {
            ch[i + 1] = (ch[i] ^ 1);
        }
    }
    int in1 = -1;
    int in2 = -1;
    for (int i = 0; i < n; ++i) {
        if (ch[i]) {
            in1 = i;
        } else {
            in2 = i;
        }
    }
    vector<int> now = query_machine(vector<int> {in1, in1, in2});
    if ((int)now.size() == 1) {
        for (int i = 0; i < n; ++i) {
            ch[i] ^= 1;
        }
    }
    vector<char> ans(n);
    for (int i = 0; i < n; ++i) {
        if (ch[i]) {
            ans[i] = 'R';
        } else {
            ans[i] = 'T';
        }
    }
    answer_type(ans);
}
