#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){
    long long n, m, k;
    cin >> n >> m >> k;
    if (n * m > 1e8){
        for (int i = 0; i < m; ++i){
            cout << "B";
        }
        return 0;
    }
    vector<pair<int, char>> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i].first >> a[i].second;
    }
    vector<string> ans(n);
    for (int i = 0; i < n; ++i){
        int j = i;
        string answer;
        while (answer.size() < m){
            answer.push_back(a[j].second);
            j = a[j].first - 1;
        }
        ans[i] = answer;
    }
    sort(ans.begin(), ans.end());
    cout << ans[k - 1] << endl;
}
