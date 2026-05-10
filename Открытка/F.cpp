#include<bits/stdc++.h>

using namespace std;

int MAX = 500;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
vector<int> topsort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    topsort.push_back(v);
}

signed main() {
    int gr, t;
    cin >> gr >> t;
    if (gr <= 1) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> cnt(n + 1);
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    cout << "? " << i << " " << j << endl;
                    string ans;
                    cin >> ans;
                    if (ans == "forward") {
                        cnt[i] += 1;
                    } else {
                        cnt[j] += 1;
                    }
                }
            }
            string ans = " ";
            for (int i = 1; i <= n; ++i) {
                if (cnt[i] <= 1) {
                    cout << "! " << i << endl;
                    cin >> ans;
                    break;
                }
            }
            if (ans == "OK") continue;
            cout << "! " << -1 << endl;
            cin >> ans;
        }
    } else if (gr == 2) {
        while (t--) {
            int n;
            cin >> n;
            set<int> st;
            for (int i = 0; i < n; ++i) {
                g[i].clear();
                used[i] = 0;
                st.insert(i);
            }
            int ss = 0;
            st.erase(ss);
            for (int i = 0; i < n - 1; ++i) {
                int k = *(st.begin());
                st.erase(st.begin());
                cout << "? " << ss + 1 << " " << k + 1 << endl;
                string ans;
                cin >> ans;
                if (ans == "forward") {
                    ss = k;
                }
            }
            cout << "! " << ss + 1 << endl;
            string ans;
            cin >> ans;
            if (ans == "WRONG") {
                return 0;
            }
        }
    } else {
        while(t--) {
            int hacnt = 0;
            int n;
            cin >> n;
            vector<vector<int>> used(n, vector<int> (n));
            set<int> st;
            vector<int> cnt(n);
            for (int i = 0; i < n; ++i) {
                st.insert(i);
            }
            int flag2 = 1;
            int minm = 0;
            while (flag2 && minm < n) {
                if (cnt[minm] > 1) {
                    flag2 = 1;
                    minm++;
                    continue;
                }
                flag2 = 0;
                if (st.size() == 0) break;
                int my = minm;
                for (int i = my + 1; i < n; ++i) {
                    if (my == i) continue;
                    if (cnt[i] > 1) continue;
                    if (!used[my][i]) {
                        used[my][i] = 1;
                        used[i][my] = 1;
                        cout << "? " << my + 1 << " " << i + 1 << endl;
                        hacnt++;
                        string ans;
                        cin >> ans;
                        if (ans == "forward") {
                            cnt[my]++;
                            if (cnt[my] > 1) st.erase(my);
                        } else {
                            cnt[i]++;
                            if (cnt[i] > 1) st.erase(i);
                        }
                        flag2 = 1;
                        break;
                    }
                }
                if (!flag2) {
                    flag2 = 1;
                    minm++;
                }
            }
            int flag = -2;
            for (int v : st) {
                if (cnt[v] > 1) continue;
                for (int i = 0; i < n; ++i) {
                    if (v == i) continue;
                    //if (cnt[i] > 1) continue;
                    if (!used[v][i]) {
                        if (hacnt >= 2000) {
                            hacnt++;
                        } else {
                            used[v][i] = 1;
                            used[i][v] = 1;
                            cout << "? " << v + 1 << " " << i + 1 << endl;
                            hacnt++;
                            string ans;
                            cin >> ans;
                            if (ans == "forward") {
                                cnt[v]++;
                            } else {
                                cnt[i]++;
                            }
                        }
                    }
                    if (cnt[v] > 1) break;
                }
                if (cnt[v] <= 1) {
                    flag = v;
                    break;
                }
            }
            if (hacnt <= 2000) {
                cout << "! " << flag + 1 << endl;
            } else {
                cout << "! " << -1 << endl;
            }
            string p;
            cin >> p;
        }
    }
    return 0;
}
