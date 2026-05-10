#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool check(vector<vector<pair<int, int>>>& ab, int ans, int t){
    if (ans == 0){
        return true;
    }
    vector<int> anses;
    for (int i = ans - 1; i < ab.size(); ++i){
        for (int j = 0; j < ab[i].size(); ++j){
            anses.push_back(ab[i][j].first);
        }
    }
    int cnt = 0;
    int i = 0;
    sort(anses.begin(), anses.end());
    while (i < anses.size() && i < ans){
        cnt += anses[i];
        i += 1;
    }
    if (cnt > 0 && t - cnt >= 0 && anses.size() >= ans){
        return true;
    } else{
        return false;
    }
}

int i_search(vector<vector<pair<int, int>>>& ab, int l, int r, int t){
    int m = (l + r) / 2;
    bool ans = check(ab, m, t);
    if (l + 1 >= r){
        if (check(ab, r, t)){
            return r;
        }
        return l;
    } else if(ans){
        return i_search(ab, m, r, t);
    } else{
        return i_search(ab, l, m, t);
    }
}
int main(){
    int k, t;
    cin >> k >> t;
    int a, b;
    vector<vector<pair<int, int>>> ab(k);
    for (int i = 0; i < k; ++i){
        cin >> b >> a;
        ab[b - 1].push_back({a, i});
    }
    int ans = i_search(ab, 0, k, t);
    vector<pair<int, int>> anses;
    for (int i = ans - 1; i < ab.size(); ++i){
        for (int j = 0; j < ab[i].size(); ++j){
            anses.push_back({ab[i][j].first, ab[i][j].second});
        }
    }
    int ans2 = anses.size();
    cout << min(ans2, ans) << endl << min(ans2, ans) << endl;
    sort(anses.begin(), anses.end());
    int i = 0;
    while (i < anses.size() && i < ans){
        cout << anses[i].second + 1 << " ";
        i += 1;
    }
    return 0;
}
