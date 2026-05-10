#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    /*int minm = 1e9, coord = -1, maxm = -1e9, coord2 = -1;
    vector<vector<int>> cnt(s.size() + 1, vector<int> (26));
    set<char> st;
    for (int i = n - 1; i >= 0; --i) {
        cnt[i] = cnt[i + 1];
        int c = (int)s[i] - 97;
        cnt[i][(int)s[i] - 97]++;
        if (c <= minm) {
            minm = c;
            coord = i;
        }
        if (c > maxm) {
            maxm = c;
            coord2 = i;
        }
        st.insert(s[i]);
    }
    if (st.size() == 1) {
         cout << s[0] << " ";
         cout << s[1] << " ";
         for (int i = 2; i < n; ++i) {
            cout << s[i];
         }
         cout << endl;
         return 0;
    }
    if (coord == n - 1 && coord2 == 0) {
        cout << ":(" << endl;
        return 0;
    }
    cout << coord << " " << coord2 << endl;
    int coord3 = coord, coord4 = coord2;
    if (coord == 0 && coord2 == n - 1) {
        int minm = 1e9, coord = -1, maxm = -1e9, coord2 = -1;
        vector<vector<int>> cnt(s.size() + 1, vector<int> (26));
        set<char> st;
        for (int i = n - 1; i >= 0; --i) {
            cnt[i] = cnt[i + 1];
            int c = (int)s[i] - 97;
            cnt[i][(int)s[i] - 97]++;
            if (c < minm) {
                minm = c;
                coord = i;
            }
            if (c >= maxm) {
                maxm = c;
                coord2 = i;
            }
            st.insert(s[i]);
        }
        cout << coord << " " << coord2 << endl;
        if (coord == 0 && coord2 == n - 1) {
            cout << ":(" << endl;
            return 0;
        }
    }
    coord = coord3;
    coord2 = coord4;
    if (coord == 0 || coord == n - 1) {
        for (int i = 0; i < coord2; ++i) {
            cout << s[i];
        }
        cout << " " << s[coord2] << " ";
        for (int i = coord2 + 1; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
    } else {
        for (int i = 0; i < coord; ++i) {
            cout << s[i];
        }
        cout << " " << s[coord] << " ";
        for (int i = coord + 1; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
    }
    //string t = "a", t2 = "aa";
    //cout << min(t, t2) << endl;
    */
    /*set<char> st;
    int to = -1;
    for (int i = 1; i < n - 1; ++i) {
        if ((s[i] > s[0] || s[i] == s[0] && i == 1) && (s[i] > s[i + 1] || s[i] == s[i + 1] && i == n - 2)) {
            to = i;
        }
        if ((s[i] < s[0] || s[i] == s[0] && i == 1) && (s[i] < s[i + 1] || s[i] == s[i + 1] && i == n - 2)) {
            to = i;
        }
        st.insert(s[i]);
    }
    st.insert(s[0]);
    st.insert(s.back());
    if (st.size() == 1) {
        cout << s[0] << " " << s[1] << " ";
        for (int i = 2; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
        return 0;
    }
    if (to == -1) {
        cout << ":(" << endl;
        return 0;
    }
    for (int i = 0; i < to; ++i) {
        cout << s[i];
    }
    cout << " " << s[to] << " ";
    for (int i = to + 1; i < n; ++i) {
        cout << s[i];
    }
    cout << endl;*/
    /*int minm = 1e9, maxm = -1e9;
    for (int i = 0; i < n; ++i) {
        minm = min(minm, (int)s[i]);
        maxm = max(maxm, (int)s[i]);
    }
    int to = -1;
    for (int i = 1; i < n - 1; ++i) {
        if ((int)s[i] == minm || (int)s[i] == maxm) {
            to = i;
        }
    }
    if (to == -1) {
        if ((int)s[0] == minm && (int)s.back() == minm) {
            cout << s[0] << " ";
            for (int i = 1; i < n - 1; ++i) {
                cout << s[i];
            }
            cout << " " << s.back() << endl;
            return 0;
        }
        if ((int)s[0] == maxm && (int)s.back() == maxm) {
            cout << s[0] << " ";
            for (int i = 1; i < n - 1; ++i) {
                cout << s[i];
            }
            cout << " " << s.back() << endl;
            return 0;
        }
    }
    for (int i = 0; i < to; ++i) {
        cout << s[i];
    }
    cout << " " << s[to] << " ";
    for (int i = to + 1; i < n; ++i) {
        cout << s[i];
    }*/
    int minm = 1e9, to1 = -1, to2 = -1, now = n - 1;
    minm = (int)s.back();
    for (int i = n - 2; i >= 1; --i) {
        if (s[i] > s[0] && (int)s[i] > minm) {
            to1 = i;
            to2 = now;
            break;
        }
        if ((int)s[i] <= minm) {
            minm = (int)s[i];
            now = i;
        }
    }
    if (to1 != -1) {
        for (int i = 0; i < to1; ++i) {
            cout << s[i];
        }
        cout << " ";
        for (int i = to1; i < to2; ++i) {
            cout << s[i];
        }
        cout << " ";
        for (int i = to2; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
        return 0;
    }
    int maxm = 1e9, to3 = -1, to4 = -1, now2 = n - 1;
    maxm = (int)s.back();
    for (int i = n - 2; i >= 1; --i) {
        if (s[i] < s[0] && (int)s[i] < maxm) {
            to3 = i;
            to4 = now2;
            break;
        }
        if ((int)s[i] >= maxm) {
            maxm = (int)s[i];
            now2 = i;
        }
    }
    if (to3 != -1) {
        for (int i = 0; i < to3; ++i) {
            cout << s[i];
        }
        cout << " ";
        for (int i = to3; i < to4; ++i) {
            cout << s[i];
        }
        cout << " ";
        for (int i = to4; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
        return 0;
    }
    set<char> st;
    for (int i = 0; i < n; ++i) {
        st.insert(s[i]);
    }
    if (st.size() == 1) {
        cout << s[0] << " " << s[1] << " ";
        for (int i = 2; i < n; ++i) {
            cout << s[i];
        }
        cout << endl;
        return 0;
    }
    //cout << 1 << endl;
    int to5 = -1;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] < s[i + 1]) {
            to5 = i;
        }
        if (s[i] > s[i + 1]) {
            to5 = i + 1;
        }
    }
    //cout << to5 << endl;
    /*if (to5 != -1 && to5 != n - 1 && to5 != 0) {
        string s1 = "", s2 = "", s3 = "";
        for (int i = 0; i < to5; ++i) {
            s1.push_back(s[i]);
        }
        s2.push_back(s[to5]);
        for (int i = to5 + 1; i < n; ++i) {
            s3.push_back(s[i]);
        }
        if (s2 >= s3 && s2 >= s1 || s2 <= s3 && s2 <= s1) {
            cout << s1 << " " << s2 << " " << s3 << endl;
            return 0;
        }
    }*/
    string s1 = "", s2 = "", s3= "";
    s1.push_back(s[0]);
    s3.push_back(s.back());
    for (int i = 1; i < n - 1; ++i) {
        s2.push_back(s[i]);
    }
    if (s2 >= s3 && s2 >= s1 || s2 <= s3 && s2 <= s1) {
        cout << s1 << " " << s2 << " " << s3 << endl;
        return 0;
    } else {
        cout << ":(" << endl;
        return 0;
    }
    /*for (int i = 1; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            string s1 = "", s2 = "", s3 = "";
            for (int l = 0; l < i; ++l) {
                s1.push_back(s[l]);
            }
            for (int l = i; l < j; ++l) {
                s2.push_back(s[l]);
            }
            for (int l = j; l < n; ++l) {
                s3.push_back(s[l]);
            }
            //cout << s1 << " " << s2 << " " << s3 << endl;
            if (s2 >= s3 && s2 >= s1 || s2 <= s3 && s2 <= s1) {
                cout << s1 << " " << s2 << " " << s3 << endl;
                return 0;
            }
        }
    }
    cout << ":(" << endl;*/
    return 0;
}
