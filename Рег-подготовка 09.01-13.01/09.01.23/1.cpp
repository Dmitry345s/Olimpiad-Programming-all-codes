#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<vector<char>> a(n, vector<char>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> a[i][j];
        }
    }
    int i = 0, j = 0;
    while (a[i][j] != '#'){
        j = 0;
        while(j < n && a[i][j] != '#'){
            ++j;
        }
        if (a[i][j] != '#'){
            ++i;
        }
    }
    int k = i, l = j;
    while (l < n && a[i][l] == '#'){
        ++l;
    }
    l -= 1;
    int size_ = l - j + 1;
    while (k < n && a[k][j] == '#'){
        ++k;
    }
    k -= 1;
    int size2_ = k - i + 1;
    int rsize = min(size_, size2_);
    int t = n - 1, v = n - 1;
    while (a[t][v] != '#'){
        v = n - 1;
        while (v >= 0 && a[t][v] != '#'){
            --v;
        }
        if (a[t][v] != '#'){
            --t;
        }
    }
    t -= rsize - 1;
    v -= rsize - 1;
    cout << rsize << endl;
    cout << i + 1 << " " << j + 1 << endl;
    cout << t + 1 << " " << v + 1 << endl;
    return 0;
}
