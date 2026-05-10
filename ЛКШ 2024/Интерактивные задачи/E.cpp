#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t, b;
    cin >> t >> b;
    while (t--) {
        int cnt = 0;
        vector<int> to_ans(b);
        int l = 0;
        vector<int> ch(2, -1);
        while (l < b / 2) {
            if (cnt % 10 == 0 && cnt != 0) {
                vector<int> to_swap(2);
                if (ch[0] != -1 && ch[1] != -1) {
                    cout << "? " << ch[0] + 1 << endl;
                    int ans;
                    cin >> ans;
                    if (ans != to_ans[ch[0]]) {
                        to_swap[0] = 1;
                    }
                    cout << "? " << ch[1] + 1 << endl;
                    cin >> ans;
                    if (ans != to_ans[ch[1]]) {
                        if (to_swap[0]) {
                            to_swap[1] = 0;
                        } else {
                            to_swap[1] = 1;
                        }
                    } else {
                        if (to_swap[0]) {
                            to_swap[1] = 1;
                        } else {
                            to_swap[1] = 0;
                        }
                    }
                    cnt += 2;
                } else if (ch[0] != -1) {
                    cout << "? " << ch[0] + 1 << endl;
                    int ans;
                    cin >> ans;
                    cout << "? " << ch[0] + 1 << endl;
                    cin >> ans;
                    if (ans != to_ans[ch[0]]) {
                        to_swap[0] = 1;
                    }
                    cnt += 2;
                } else if (ch[1] != -1) {
                    cout << "? " << ch[1] + 1 << endl;
                    int ans;
                    cin >> ans;
                    cout << "? " << ch[1] + 1 << endl;
                    cin >> ans;
                    if (ans != to_ans[ch[1]]) {
                        to_swap[1] = 1;
                    }
                    cnt += 2;
                }
                for (int i = 0; i < b / 2; ++i) {
                    if (to_swap[0]) {
                        to_ans[i] ^= 1;
                        to_ans[b - i - 1] ^= 1;
                    }
                    if (to_swap[1]) {
                        swap(to_ans[i], to_ans[b - i - 1]);
                    }
                }
            }
            cout << "? " << l + 1 << endl;
            cin >> to_ans[l];
            cout << "? " << b - l - 1 + 1 << endl;
            cin >> to_ans[b - l - 1];
            if (to_ans[l] != to_ans[b - l - 1]) {
                ch[1] = l;
            } else {
                ch[0] = l;
            }
            cnt += 2;
            l++;
        }
        cout << "! ";
        for (int i = 0; i < b; ++i) {
            cout << to_ans[i];
        }
        cout << endl;
        string s;
        cin >> s;
    }
    return 0;
}
