#include<iostream>
#include<vector>

using namespace std;

void func(int i, int j, vector<vector<char>>& g, string s, int temp, string path) {
    if (temp == 5 && s =) {
        return;
    }
    set<char> st;
    for (auto u : s) {
        st.insert(s);
    }
    if (st.find(g[i + 1][j]) != st.end()) {
        func(i + 1, j, g, s + g[i + 1][j], temp + 1, path + "u");
    }
    if (st.find(g[i - 1][j]) != st.end()) {
        func(i - 1, j, g, s + g[i - 1][j], temp + 1, path + "d");
    }
    if (st.find(g[i][j + 1]) != st.end()) {
        func(i, j+ 1, g, s + g[i][j + 1], temp + 1, path + "r");
    }
    if (st.find(g[i][j - 1]) != st.end()) {
        func(i, j - 1, g, s + g[i][j - 1], temp + 1, path + "l");
    }
}
int main() {
    long long n, m, a, b, c;
    cin >> n >> m;
    vector<vector<char>> g(n + 8, vector<char> (m + 8, 'A'));
    for (int i = 4; i < n + 4; ++i) {
        for (int j = 4; j < n + 4; ++j) {
            cin >> g[i][j];
        }
    }
    for (int i = 0; i < n + 8; ++i) {
        for (int j = 0; j < m + 8; ++j) {
            if (g[i][j] == 'H') {
                func(i, j, g, "", 0);
            }
        }
    }
    return 0;
}
