#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long cnt = 0;

vector<int> mergef(vector<int> a, vector<int> b) {
    vector<int> ans;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            ans.push_back(a[i]);
            ++i;
        } else {
            ans.push_back(b[j]);
            ++j;
            cnt += a.size() - i;
        }
    }
    if (i < a.size()) {
        for (int l = i; l < a.size(); ++l) {
            ans.push_back(a[l]);
        }
    } else if (j < b.size()) {
        for (int l = j; l < b.size(); ++l) {
            ans.push_back(b[l]);
        }
    }
    return ans;
}

vector<int> merge_sort(vector<int> s) {
    if (s.size() == 1) {
        return s;
    }
    vector<int> a, b;
    for (int i = 0; i < s.size() / 2; ++i) {
        a.push_back(s[i]);
    }
    for (int i = s.size() / 2; i < s.size(); ++i) {
        b.push_back(s[i]);
    }
    return mergef(merge_sort(a), merge_sort(b));
}
int main() {
    int n, l;
    cin >> n >> l;
    vector<pair<long long, int>> w(n);
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        w[i].first = i + x * l;
        w[i].second = i;
    }
    sort(w.begin(), w.end());
    vector<int> for_sort(n);
    for (int i = 0; i < n; ++i) {
        for_sort[i] = w[i].second;
    }
    for_sort = merge_sort(for_sort);
    cout << cnt << endl;
}
