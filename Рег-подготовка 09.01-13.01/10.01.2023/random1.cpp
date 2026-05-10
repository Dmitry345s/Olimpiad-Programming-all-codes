#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    int ans = 0, ans2 = 0;
    vector<pair<int, int>> a;
    vector<pair<int, int>> c;
    bool flag = false;
    for (int i = 0; i < n; ++i){
        string now;
        cin >> now;
        int cet = 0, ncet = 0, size_ = 0;
        for (int j = 0; j < now.size(); ++j){
            if (now[j] == 'B' && j % 2 == 0){
                cet += 1;
            } else if (now[j] == 'B' && j % 2 == 1){
                ncet += 1;
            }
            size_ += 1;
        }
        if (size_ % 2 == 1){
            flag = true;
            a.push_back({cet, ncet});
            c.push_back({cet - ncet, a.size() - 1});
        } else{
            ans += max(cet, ncet);
            ans2 += cet;
        }
    }
    if (!flag){
        cout << ans2 << endl;
        return 0;
    }
    sort(c.begin(), c.end());
    reverse(c.begin(), c. end());
    for (int i = 0; i < c.size() / 2; ++i){
        ans += a[c[i].second].first + a[c[c.size() - i - 1].second].second;
    }
    if (c.size() % 2 == 1){
        ans += a[c[c.size() / 2].second].first;
    }
    cout << ans << endl;
    return 0;
}
