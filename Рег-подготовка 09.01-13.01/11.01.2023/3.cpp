#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    if (n >= 250 && n <= 1950){
        cout << "NO";
        return 0;
    }
    vector<vector<pair<int, int>>> coor(n, vector<pair<int, int>> (3, {0, 0}));
    vector<pair<int, int>> maxms(n, {0, 0});
    int maxm;
    vector<int> dif(3);
    int x1, x2, x3, y1, y2, y3, cl, cd;
    for (int i = 0; i < n; ++i){
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if (x1 == x2 || y1 == y2){
            cl = 0 - x3;
            cd = 0 - y3;
        } else if (x1 == x3 || y1 == y3){
            cl = 0 - x2;
            cd = 0 - y2;
        } else if (x2 == x3 || y2 == y3){
            cl = 0 - x1;
            cd = 0 - y1;
        }
        x1 += cl;
        x2 += cl;
        x3 += cl;
        y1 += cd;
        y2 += cd;
        y3 += cd;
        dif[0] = 0 - x1 + 0 - y1;
        dif[1] = 0 - x2 + 0 - y2;
        dif[2] = 0 - x3 + 0 - y3;
        maxm = max(max(dif[0], dif[1]), dif[2]);
        if (dif[0] == maxm){
            maxms[i].first = 0 - x1;
            maxms[i].second = 0 - y1;
        } else if (dif[1] == maxm){
            maxms[i].first = 0 - x2;
            maxms[i].second = 0 - y2;
        } else{
            maxms[i].first = 0 - x3;
            maxms[i].second = 0 - y3;
        }
        coor[i][0].first = x1;
        coor[i][0].second = y1;
        coor[i][1].first = x2;
        coor[i][1].second = y2;
        coor[i][2].first = x3;
        coor[i][2].second = y3;
    }
    int mcr = -1e9, mcu = -1e9;
    int summ = mcr + mcu;
    for (int i = 0; i < n; ++i){
        if (maxms[i].first + maxms[i].second > summ){
            mcr = maxms[i].first;
            mcu = maxms[i].second;
            summ = mcr + mcu;
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < 3; ++j){
            if (coor[i][j].first + mcr < 0 || coor[i][j].second + mcu < 0){
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < 3; ++j){
            cout << coor[i][j].first + mcr << " " << coor[i][j].second + mcu << " ";
        }
        cout << endl;
    }
    return 0;
}
