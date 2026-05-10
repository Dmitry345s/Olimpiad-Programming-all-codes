#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a, b;
    int now;
    for (int i = 0; i < n; ++i){
        cin >> now;
        if (i % 2 == 0){
            for (int j = 0; j < now; ++j){
                a.push_back(1);
            }
        } else{
            for (int j = 0; j < now; ++j){
                a.push_back(0);
            }
        }
    }
    for (int i = 0; i < m; ++i){
        cin >> now;
        if (i % 2 == 0){
            for (int j = 0; j < now; ++j){
                b.push_back(1);
            }
        } else{
            for (int j = 0; j < now; ++j){
                b.push_back(0);
            }
        }
    }
    vector<int> b2;
    vector<int> a2;
    if (a.size() > b.size()){
        for (int i = 0; i < a.size() - b.size(); ++i){
            b2.push_back(0);
            a2.push_back(a[i]);
        }
        for (int i = 0; i < b.size(); ++i){
            b2.push_back(b[i]);
            a2.push_back(a[i + a.size() - b.size()]);
        }
    } else if (b.size() >= a.size()){
        for (int i = 0; i < b.size() - a.size(); ++i){
            a2.push_back(0);
            b2.push_back(b[i]);
        }
        for (int i = 0; i < a.size(); ++i){
            a2.push_back(a[i]);
            b2.push_back(b[i + b.size() - a.size()]);
        }
    }
    vector<int> c(a2.size());
    for (int i = a2.size() - 1; i >= 0; --i){
        c[i] = (a2[i] + b2[i]) % 2;
    }
    long long cnt = 1;
    vector<long long> ans;
    for (int i = 1; i < c.size(); ++i){
        if (c[i] != c[i - 1]){
            ans.push_back(cnt);
            cnt = 1;
        } else{
            cnt += 1;
        }
    }
    ans.push_back(cnt);
    int j = 0;
    if (c[0] == 0){
        j = 1;
    }
    for (int i = j; i < ans.size(); ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
