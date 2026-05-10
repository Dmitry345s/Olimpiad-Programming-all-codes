#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

int main() {
    vector<string> a(8);
    for (int i = 0; i < 8; ++i) {
        cin >> a[i];
    }
    int num = 0;
    map<string, int> mp;
    map<int, string> mp2;
    map<int, pair<int, int>> mp3;
    vector<vector<int>> g;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (a[i][j] == 'Q') {
                char k = char(j + 97), k2 = char(8 - i + int('0'));
                string s;
                s.push_back(k);
                s.push_back(k2);
                mp[s] = num;
                mp2[num] = s;
                mp3[num] = {i, j};
                ++num;
            }
        }
    }
    for (int _ = 0; _ < num; ++_) {
    vector<pair<int, vector<string>>> cnt(num);
    for (int i = 0; i < num; ++i) {
        pair<int, int> now = mp3[i];
        int l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l += 1;
            j += 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l -= 1;
            j -= 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l += 1;
            j -= 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l -= 1;
            j += 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            j += 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l += 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            j -= 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        l = now.first, j = now.second;
        while (l < 8 && j < 8 && a[l][j] == '.') {
            l -= 1;
        }
        if (a[l][j] == 'Q') {
            cnt[i].first += 1;
            char k = char(j + 97), k2 = char(8 - i + int('0'));
            string s;
            s.push_back(k);
            s.push_back(k2);
            cnt[i].second.push_back(s);
        }
        bool flag = true;
        for (int j = 0; j < num; ++j) {
            pair<int, int> next = mp3[j];
            if (cnt[j].first == 0) {
                cout << "NO SOLUTION" << endl;
                return 0;
            } else if (cnt[j].first == 1 && a[next.first][next.second] != '.') {
                cout << mp2[j] << ":" << cnt[j].second[0] << endl;
                a[next.first][next.second] = '.';
                flag = false;
                break;
            }
        }
        if (flag) {
            for (int j = 0; j < num; ++j) {
                pair<int, int> next = mp3[j];
                if (a[next.first][next.second] == 'Q') {
                    cout << mp2[j] << ":" << cnt[j].second[0] << endl;
                    a[next.first][next.second] = '.';
                    break;
                }
            }
        }
    }
    }
    return 0;
}
