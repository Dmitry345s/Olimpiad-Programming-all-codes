#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int cnt = 0;
    vector<int> a(n);
    vector<int> p(n + 1);
    vector<pair<vector<int>, vector<int>>> centers(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[i + 1] = p[i];
        if (a[i] == i + 1) {
            p[i + 1] += 1;
            cnt += 1;
        }
        int center = a[i] - 1 + i;
        if (center % 2 == 0) {
            centers[center / 2].first.push_back(min(i, a[i] - 1));
        } else {
            centers[center / 2].second.push_back(min(i, a[i] - 1));
        }
    }
    int maxm = 0, left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        sort(centers[i].first.begin(), centers[i].first.end());
        for (int j = centers[i].first.size() - 1; j >= 0; --j) {
            int l = centers[i].first[j], r = i + (i - l);
            //cout << l << " " << r << " " << j << " " << p[l] << " " << p[r + 1] << endl;
            int may_maxm = centers[i].first.size() - 1 - j + p[l] + cnt - p[r + 1];
            if (a[i] == i + 1) {
                may_maxm += 1;
            }
            //cout << may_maxm << endl;
            if (may_maxm >= maxm) {
                left = a[l];
                right = a[r];
                maxm = may_maxm;
            }
        }
        sort(centers[i].second.begin(), centers[i].second.end());
        for (int j = centers[i].second.size() - 1; j >= 0; --j) {
            int l = centers[i].second[j], r = i + (i - l) + 1;
            int may_maxm = centers[i].second.size() - 1 - j + p[l] + cnt - p[r + 1];
            //cout << l << " " << r << " " << j << " " << p[l] << " " << p[r + 1] << " " << may_maxm << endl;
            if (may_maxm >= maxm) {
                left = a[l];
                right = a[r];
                maxm = may_maxm;
            }
        }
    }
    cout << left << " " << right << endl;
    return 0;
}
