#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, char>> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i].first >> a[i].second;
    }
    vector<pair<int, int>> parents(n, {-1, -1});
    vector<pair<string, int>> ans(n, {"", -1});
    map<int, string> components;
    for (int i = 0; i < n; ++i){
        if (parents[i].first != -1){
            string cicle = components[parents[i].first];
            if (ans[i].second == -1){
                string t = cicle.substr(0, parents[i].second);
                ans[i].first = cicle.substr(parents[i].second, cicle.size() - parents[i].second) + t;
            } else{
                ans[i].first = cicle.substr(parents[i].second, cicle.size() - parents[i].second);
            }
            continue;
        }
        int j = i;
        int cnt = 0;
        string component;
        while (parents[j].first == -1 || ans[j].second != -1){
            component.push_back(a[j].second);
            parents[j] = {i, cnt};
            cnt += 1;
            j = a[j].first - 1;
        }
        if (i == j){
            components[i] = component;
            ans[i].first = component;
        } else{
            components[i] = component;
            ans[i].first = component;
            ans[i].second = j;
        }
    }
    for (int i = 0; i < n; ++i){
        string answer = "";
        int l;
        int size_ = ans[i].first.size();
        if (ans[i].second != -1){
            answer += ans[i].first.substr(0, min(size_, m));
            l = ans[i].second;
            m -= size_;
        } else{
            l = i;
        }
        if (m > 0){
            for (int j = 0; j < m / ans[l].first.size(); ++j){
                answer += ans[l].first;
            }
            answer += ans[l].first.substr(0, m % ans[l].first.size());
        }
        if (l != i){
            m += size_;
        }
        ans[i].first = answer;
    }
    sort(ans.begin(), ans.end());
    cout << ans[k - 1].first << endl;
    return 0;
}
