#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> a(n, {0, {0, 0}});
    bool flag = false;
    for (int i = 0; i < n; ++i){
        string now;
        cin >> now;
        for (int j = 0; j < now.size(); ++j){
            if (now[j] == 'B' && j % 2 == 0){
                a[i].second.first += 1;
            } else if (now[j] == 'B' && j % 2 == 1){
                a[i].second.second += 1;
            }
        }
        int x;
        if (a[i].second.first >= a[i].second.second){
            x = -1;
        } else{
            x = 1;
        }
        a[i].first = x + now.size() % 2;
        if (a[i].first == 0 || a[i].first == 2){
            flag = true;
        }
    }
    sort(a.begin(), a.end());
    if (!flag){
        int cnt = 0;
        for (int i = 0; i < n; ++i){
            cnt += a[i].second.first;
        }
        cout << cnt << endl;
    } else{
        int cnt = 0;
        vector<pair<int, pair<int, int>>> b;
        vector<pair<int, int>> c;
        for (int i = 0; i < n; ++i){
            if (a[i].first == -1 || a[i].first == 1){
                cnt += max(a[i].second.first, a[i].second.second);
            } else{
                b.push_back(a[i]);
                c.push_back({a[i].second.first - a[i].second.second, b.size() - 1});
            }
        }
        int count2 = 0;
        for (int i = 0; i < b.size(); ++i){
            count2 += b[i].first;
        }
        count2 /= 2;
        int count0 = b.size() - count2;
        sort(c.begin(), c.end());
        if (count2 < count0){
            for (int i = 0; i < c.size(); ++i){
                if (c[i].first < 0){
                    cnt += max(b[c[i].second].second.second, b[c[i].second].second.first);
                } else if (c[i].first >= 0){
                    if (i - count2 < (count0 - count2 + 1) / 2){
                        cnt += b[c[i].second].second.first;
                    } else{
                        cnt += b[c[i].second].second.second;
                    }
                }
            }
        } else{
            reverse(c.begin(), c.end());
            for (int i = 0; i < c.size(); ++i){
                if (c[i].first >= 0){
                    cnt += max(b[c[i].second].second.second, b[c[i].second].second.first);
                } else if (c[i].first < 0){
                    if (i - count0 <= (count2 - count0 + 1) / 2){
                        cnt += b[c[i].second].second.second;
                    } else{
                        cnt += b[c[i].second].second.first;
                    }
                }
            }
        }
        cout << cnt + 2 << endl;
    }
    return 0;
}
