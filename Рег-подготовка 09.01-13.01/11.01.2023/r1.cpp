#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; ++i){
        cin >> b[i];
    }
    int an = a.size() % 2, bn = b.size() % 2;
    int na = (an + bn) % 2, la = (na + 1) % 2;
    vector<long long> ans;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 && j >= 0){
        if (a[i] < b[j]){
            b[j] -= a[i];
            if (la == na){
                ans.back() += a[i];
            } else{
                ans.push_back(a[i]);
            }
            a[i] = 0;
            i -= 1;
            an += 1;
            an %= 2;
            la = na;
            na = (an + bn) % 2;

        } else if (b[j] < a[i]){
            a[i] -= b[j];
            if (la == na){
                ans.back() += b[j];
            } else{
                ans.push_back(b[j]);
            }
            b[j] = 0;
            j -= 1;
            bn += 1;
            bn %= 2;
            la = na;
            na = (an + bn) % 2;
        } else{
            if (la == na){
                ans.back() += b[j];
            } else{
                ans.push_back(a[i]);
            }
            b[j] = 0;
            a[i] = 0;
            i -= 1;
            j -= 1;
            an += 1;
            an %= 2;
            bn += 1;
            bn %= 2;
            la = na;
            na = (an + bn) % 2;
        }
    }
    if (i < 0 && j >= 0){
        if (la == na){
            ans.back() += b[j];
        } else{
            ans.push_back(b[j]);
        }
        b[j] = 0;
        j -= 1;
        for (int l = j; l >= 0; --l){
            ans.push_back(b[l]);
        }
    } else if (j < 0 && i >= 0){
        if (la == na){
            ans.back() += a[i];
        } else{
            ans.push_back(a[i]);
        }
        a[i] = 0;
        i -= 1;
        for (int l = i; l >= 0; --l){
            ans.push_back(a[l]);
        }
    }
    int k = 1;
    if (a.size() % 2 == b.size() % 2 && ans.size() % 2 == 1 || a.size() % 2 != b.size() % 2 && ans.size() % 2 == 0){
        k += 1;
    }
    for (int i = ans.size() - k; i >= 0; --i){
        cout << ans[i] << " ";
    }
    return 0;
}
