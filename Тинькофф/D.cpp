#pragma GCC optimize("inline")
#pragma GCC optimize("inline-functions")
#include<iostream>
#include<vector>
#include<map>

using namespace std;

map<int, int> counter;
map<int, int> :: iterator it;
int num = 0;

int deform(int n){
    int sim;
    if (n < 0){
        n *= -1;
        sim = -1;
    } else{
        sim = 1;
    }
    int sum = 1;
    if (n == 0){
        return -1;
    }
    int i = 2;
    int a = n;
    pair<int, int> factor = {0, 0};
    while (i * i <= a){
        if (n % i == 0){
            if (factor.first == i){
                factor.second += 1;
            } else{
                factor = {i, 1};
            }
            n /= i;
        } else{
            if (factor.first != 0){
                if (factor.second % 2 == 1){
                    sum *= factor.first;
                }
            }
            factor = {0, 0};
            i += 1;
        }
    }
    if (factor.first != 0 && factor.second % 2 == 1){
        sum *= factor.first;
    }
    if (n > 1){
        sum *= n;
    }
    int ans = sum * sim;
    it = counter.find(ans);
    if (counter.size() > 0 && it == counter.end()){
        num += 1;
        counter[ans] = num;
        return num;
    } else if (counter.size() == 0){
        counter[ans] = num;
        return num;
    } else{
        return it->second;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int now;
    vector<int> b(n);
    for (int i = 0; i < n; ++i){
        cin >> now;
        b[i] = deform(now);
    }
    vector<int> ans(n);
    int x = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i){
        vector<int> a(num + 1, 0);
        x = 0;
        cnt = 0;
        for (int j = i; j < n; ++j){
            if (b[j] != -1){
                if (a[b[j]] == 0){
                    cnt += 1;
                }
                a[b[j]] += 1;
            }
            if (cnt == 0){
               ans[0] += 1;
            } else{
                ans[cnt - 1] += 1;
            }
        }
    }
    for (int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " ";
    }
    return 0;
}
