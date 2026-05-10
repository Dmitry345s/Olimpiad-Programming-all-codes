#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int t, l, r;
    if (q == 1){
        cin >> t >> l >> r;
        vector<pair<char, int>> st;
        vector<long long> a(n, 0);
        long long ans = 0;
        for (int i = l - 1; i <= r - 1; ++i){
            if (st.size() == 0 || st.back().first == ')' || s[i] == '('){
                st.push_back({s[i], i});
                continue;
            }
            if (st.back().second > 0){
                a[i] = a[st.back().second - 1];
            }
            a[i] += 1;
            ans += a[i];
            st.pop_back();
        }
        cout << ans << endl;
        return 0;
    }
    vector<long long> a(n, 0);
    vector<int> b;
    vector<pair<char, int>> st;
    vector<pair<int, int>> qs;
    for (int i = 0; i < q; ++i){
        cin >> t >> l >> r;
        qs.push_back({r - 1, i + 1});
        qs.push_back({l - 1, -i - 1});
    }
    sort(qs.begin(), qs.end());
    vector<int> opens(q + 1, -1);
    int j = 0;
    int now = 0;
    for (int i = 0; i < n; ++i){
        while (j < qs.size() && i == qs[j].first && qs[j].second < 0){
            opens[-qs[j].second] = now;
            ++j;
        }
        if (st.size() == 0 || st.back().first == ')' || s[i] == '('){
                st.push_back({s[i], i});
                continue;
            }
            if (st.back().second > 0){
                a[i] = a[st.back().second - 1];
            }
            a[i] += 1;
            now += a[i];
            st.pop_back();
        while (j < qs.size() && i == qs[j].first && qs[j].second > 0){
            opens[qs[j].second] = now - opens[qs[j].second];
            ++j;
        }
    }
    for (int i = 1; i < opens.size(); ++i){
        cout << opens[i] << endl;
    }
    return 0;
}
