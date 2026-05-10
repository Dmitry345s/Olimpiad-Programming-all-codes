#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

vector<vector<int>> g(1e5);
vector<int> used(1e5);

void dfs(int v, vector<int> & high) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            high[to] = high[v] + 1;
            dfs(to, high);
        }
    }
}
int main() {
    int n;
    cin >> n;
    vector<int> counter(n), high(n);
    map<string, int> mp;
    map<int, string> mp2;
    int num = 0;
    for (int i = 0; i < n - 1; ++i) {
        string to, p;
        cin >> to >> p;
        if (mp.find(p) == mp.end()) {
            mp[p] = num;
            mp2[num] = p;
            ++num;
        }
        if (mp.find(to) == mp.end()) {
            mp[to] = num;
            mp2[num] = to;
            ++num;
        }
        counter[mp[to]] += 1;
        g[mp[p]].push_back(mp[to]);
    }
    for (int i = 0; i < n; ++i) {
        if (!counter[i]) {
            dfs(i, high);
        }
    }
    vector<pair<string, int>> ans;
    for (int i = 0; i < n; ++i) {
        ans.push_back({mp2[i], high[i]});
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < n; ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}
