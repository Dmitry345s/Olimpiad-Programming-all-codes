#include<bits/stdc++.h>

using namespace std;

string dof(string s, int n) {
    string ans;
    ans.assign(n, 'N');
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ans[i] = 'X';
        } else if (s[i + n] == '1') {
            ans[i] = 'Y';
        }
    }
    return ans;
}

string dot(string s, int n) {
    array<int, 3> cnt = {0, 0, 0};
    map<char, string> mp;
    mp['X'] = "100";
    mp['Y'] = "010";
    mp['N'] = "001";
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'X') {
            cnt[0]++;
        } else if (s[i] == 'Y') {
            cnt[1]++;
        } else {
            cnt[2]++;
        }
    }
    vector<pair<int, char>> all;
    all.push_back({cnt[0], 'X'});
    all.push_back({cnt[1], 'Y'});
    all.push_back({cnt[2], 'N'});
    sort(all.rbegin(), all.rend());
    string ans;
    for (int i = 0; i < 2; ++i) {
        for (auto c : mp[all[i].second]) {
            ans.push_back(c);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == all[0].second) {
            ans.push_back('1');
        } else {
            ans.push_back('0');
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == all[0].second) continue;
        if (s[i] == all[1].second) {
            ans.push_back('1');
        } else {
            ans.push_back('0');
        }
    }
    return ans;
}

string dof2(string s, int n) {
    //return s;
    string ans;
    ans.resize(n);
    map<string, char> mp;
    mp["100"] = 'X';
    mp["010"] = 'Y';
    mp["001"] = 'N';
    set<char> st = {'X', 'Y', 'N'};
    string s1;
    for (int i = 0; i < 3; ++i) {
        s1.push_back(s[i]);
    }
    char c[3];
    c[0] = mp[s1];
    string s2;
    for (int i = 3; i < 6; ++i) {
        s2.push_back(s[i]);
    }
    c[1] = mp[s2];
    st.erase(c[0]);
    st.erase(c[1]);
    c[2] = *st.begin();
    //cout << c[0] << " " << c[1] << " " << c[2] << endl;
    for (int i = 6; i < n + 6; ++i) {
        if (s[i] == '1') {
            ans[i - 6] = c[0];
        }
    }
    int l = 0;
    for (int i = 6; i < n + 6; ++i) {
        if (s[i] == '1') continue;
        if (s[n + 6 + l] == '1') {
            ans[i - 6] = c[1];
        } else {
            ans[i - 6] = c[2];
        }
        l++;
    }
    return ans;
}

string dot2(string s, int n) {
    int fl = 0;
    string ans;
    for (int i = 0; i < n; ++i) {
        if (!fl && s[i] == 'X') {
            ans.push_back('1');
            fl = 1;
            continue;
        }
        if (!fl || s[i] != 'N') {
            ans.push_back('0');
        } else {
            ans.push_back('1');
        }
    }
    return ans;
}

string dof3(string s, int n) {
    int fl = 0;
    string ans;
    for (int i = 0; i < n; ++i) {
        if (!fl && s[i] == '1') {
            ans.push_back('X');
            fl = 1;
            continue;
        }
        if (!fl || s[i] == '0') {
            ans.push_back('Y');
            continue;
        }
        ans.push_back('N');
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tp, n;
    cin >> tp >> n;
    string s;
    cin >> s;
    if (tp == 1) {
        cout << dot2(s, n) << endl;
    } else {
        string now = dof3(s, n);
        //cout << now << endl;
        vector<int> st;
        vector<int> ans;
        int fl = 0;
        for (int i = 0; i < n; ++i) {
            if (now[i] == 'X') fl = 1;
            if (!fl) {
                ans.push_back(i);
                continue;
            }
            if (now[i] == 'Y') {
                /*while (!st.empty() && (now[st.back()] == 'N' || now[st.back()] == 'Y')) {
                    ans.push_back(st.back());
                    st.pop_back();
                }*/
                st.push_back(i);
            } else if (now[i] == 'N') {
                while ((int)st.size() > 1 || !st.empty() && now[st.back()] != 'X') {
                    ans.push_back(st.back());
                    st.pop_back();
                }
                //st.push_back(i);
                ans.push_back(i);
            } else {
                /*while (!st.empty() && now[st.back()] == 'X') {
                    ans.push_back(st.back());
                    st.pop_back();
                }*/
                st.push_back(i);
            }
        }
        while (!st.empty()) {
            ans.push_back(st.back());
            st.pop_back();
        }
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
