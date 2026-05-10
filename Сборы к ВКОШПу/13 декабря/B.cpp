// #define _GLIBCXX_DEBUG
#include<bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

const int MAXN = 502;

int n, m;
vector<string> table;
bool is_access[8][MAXN][MAXN];
vector<int> ancestor[8][MAXN][MAXN];
char ans[1000001];
int cnt = 0;

void solve(int x1, int y1, int x2, int y2) {
    cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int cur_mask = 0; cur_mask < 8; cur_mask++) {
                is_access[cur_mask][i][j] = false;
                ancestor[cur_mask][i][j] = {};
            }
        }
    }
    is_access[4][x1][y1] = true;
    queue<vector<int>> cur_q;
    cur_q.push({4, x1, y1});
    vector<pair<int, int>> go = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (cur_q.size()) {
        vector<int> cur_state = cur_q.front();
        vector<int> next_state = cur_state;
        next_state[0] ^= 4;
        cur_q.pop();
        for (auto cur_go : go) {
            next_state = cur_state;
            next_state[0] ^= 4;
            next_state[1] = cur_state[1] + cur_go.first;
            next_state[2] = cur_state[2] + cur_go.second;
            if (next_state[1] < 0 || next_state[1] >= n || next_state[2] < 0 || next_state[2] >= m) {
                continue;
            }
            if (table[next_state[1]][next_state[2]] == 'W' && table[cur_state[1]][cur_state[2]] == 'W') {
                next_state[0] |= 2;
            }
            if (table[next_state[1]][next_state[2]] == 'B' && table[cur_state[1]][cur_state[2]] == 'B') {
                next_state[0] |= 1;
            }
            if (is_access[next_state[0]][next_state[1]][next_state[2]]) continue;
            is_access[next_state[0]][next_state[1]][next_state[2]] = true;
            ancestor[next_state[0]][next_state[1]][next_state[2]] = cur_state;
            cur_q.push(next_state);
        }
    }
    vector<int> pos_balance = {1, 2};
    for (auto need_balance : pos_balance) {
        vector<int> cur_state = {need_balance, x2, y2};
        vector<vector<int>> cur_path = {};
        int cur_balance = 0;
        if (table[x2][y2] == 'B') {
            cur_balance++;
        } else {
            cur_balance--;
        }
        cur_path.push_back(cur_state);
    //        cout << cur_state[0] << endl;
        while (cur_state.size()) {
            cur_state = ancestor[cur_state[0]][cur_state[1]][cur_state[2]];
            if (!cur_state.size()) break;
            cur_path.push_back(cur_state);
            if (table[cur_state[1]][cur_state[2]] == 'B') {
                cur_balance++;
            } else {
                cur_balance--;
            }
        }
        if (cur_balance == 0) {
            reverse(cur_path.begin(), cur_path.end());
    //        cout << cur_path[0][1] << " cur_path " << cur_path[0][2] << " " << cur_path[1][1] << " " << cur_path[1][2] << endl;
    //        cout << cur_path.back()[1] << " cur_path " << cur_path.back()[2] << " " << x2 << " " << y2 << " " << cur_balance << endl;
            string ans = "";
    //        cout << cur_path.size() << endl;
            for (int i = 1; i < (int)cur_path.size(); i++) {
    //            cout << i << endl;
                string cur_cycle = "";
                if (cur_path[i][1] == cur_path[i - 1][1] - 1) {
                    cur_cycle = "DU";
                }
                if (cur_path[i][1] == cur_path[i - 1][1] + 1) {
                    cur_cycle = "UD";
                }
                if (cur_path[i][2] == cur_path[i - 1][2] - 1) {
                    cur_cycle = "RL";
                }
                if (cur_path[i][2] == cur_path[i - 1][2] + 1) {
                    cur_cycle = "LR";
                }
                ans[cnt++] = cur_cycle[1];
    //            cout << cur_cycle.size() << endl;
                if ((cur_path[i][0] ^ cur_path[i - 1][0]) & 2) {
                    if (cur_balance > 0) {
                        while (cur_balance) {
    //                        cout << "!" << endl;
                            ans[cnt++] = cur_cycle[0];
                            ans[cnt++] = cur_cycle[1];
                            cur_balance -= 2;
                        }
                    }
                }
                if ((cur_path[i][0] ^ cur_path[i - 1][0]) & 1) {
                    if (cur_balance < 0) {
    //                    cout << cur_balance << endl;
                        while (cur_balance) {
                            ans[cnt++] = cur_cycle[0];
                            ans[cnt++] = cur_cycle[1];
                            cur_balance += 2;
                        }
                    }
                }
            }
            cout << cnt + 1 << " ";
            for (int i = 0; i < cnt; i++) {
                cout << ans[i];
            }
            cout << endl;
            return;
        }
    }
    if (is_access[0][x2][y2] || is_access[3][x2][y2]) {
        vector<int> cur_state = {3, x2, y2};
        if (is_access[0][x2][y2]) {
            cur_state[0] = 0;
        }
        vector<vector<int>> cur_path = {};
        int cur_balance = 0;
        if (table[x2][y2] == 'B') {
            cur_balance++;
        } else {
            cur_balance--;
        }
        cur_path.push_back(cur_state);
//        cout << cur_state[0] << endl;
        while (cur_state.size()) {
            cur_state = ancestor[cur_state[0]][cur_state[1]][cur_state[2]];
            if (!cur_state.size()) break;
            cur_path.push_back(cur_state);
            if (table[cur_state[1]][cur_state[2]] == 'B') {
                cur_balance++;
            } else {
                cur_balance--;
            }
        }
        reverse(cur_path.begin(), cur_path.end());
//        cout << cur_path[0][1] << " cur_path " << cur_path[0][2] << " " << cur_path[1][1] << " " << cur_path[1][2] << endl;
//        cout << cur_path.back()[1] << " cur_path " << cur_path.back()[2] << " " << x2 << " " << y2 << " " << cur_balance << endl;
        string ans = "";
//        cout << cur_path.size() << endl;
        for (int i = 1; i < (int)cur_path.size(); i++) {
//            cout << i << endl;
            string cur_cycle = "";
            if (cur_path[i][1] == cur_path[i - 1][1] - 1) {
                cur_cycle = "DU";
            }
            if (cur_path[i][1] == cur_path[i - 1][1] + 1) {
                cur_cycle = "UD";
            }
            if (cur_path[i][2] == cur_path[i - 1][2] - 1) {
                cur_cycle = "RL";
            }
            if (cur_path[i][2] == cur_path[i - 1][2] + 1) {
                cur_cycle = "LR";
            }
            ans[cnt++] = cur_cycle[1];
//            cout << cur_cycle.size() << endl;
            if ((cur_path[i][0] ^ cur_path[i - 1][0]) & 2) {
                if (cur_balance > 0) {
                    while (cur_balance) {
//                        cout << "!" << endl;
                        ans[cnt++] = cur_cycle[0];
                        ans[cnt++] = cur_cycle[1];
                        cur_balance -= 2;
                    }
                }
            }
            if ((cur_path[i][0] ^ cur_path[i - 1][0]) & 1) {
                if (cur_balance < 0) {
//                    cout << cur_balance << endl;
                    while (cur_balance) {
                        ans[cnt++] = cur_cycle[0];
                        ans[cnt++] = cur_cycle[1];
                        cur_balance += 2;
                    }
                }
            }
        }
        ///ans.erase(ans.begin());
//        assert((int)ans.size() + 1 <= 1000000);
        cout << cnt + 1 << " ";
        for (int i = 0; i < cnt; i++) {
            cout << ans[i];
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    table.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> table[i];
    }
    int q, x1, y1, x2, y2;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;
        solve(x1, y1, x2, y2);
    }
}
