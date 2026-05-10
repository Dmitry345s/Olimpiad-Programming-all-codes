#include<iostream>
#include<vector>

using namespace std;

struct palka{
    int x1, x2, y1, y2;
};

vector<vector<int>> g(5000);
vector<int> used(5000), top_sort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    top_sort.push_back(v);
}

bool check(palka a, palka b) {
    if (b.x1 >= a.x1 && a.x2 >= b.x2) {
        double amid = (a.y1 + a.y2), bmid = (b.y1 + b.y2);
        amid /= 2;
        bmid /= 2;
        if (amid >= bmid) {
            return true;
        } else {
            return false;
        }
    }
    if (b.x1 <= a.x1 && a.x2 <= b.x2) {
        double amid = (a.y1 + a.y2), bmid = (b.y1 + b.y2);
        amid /= 2;
        bmid /= 2;
        if (amid >= bmid) {
            return true;
        } else {
            return false;
        }
    } else if (a.x1 >= b.x1 && a.x1 <= b.x2 && a.y1 >= min(b.y1, b.y2)) {
        return true;
    } else if (a.x2 >= b.x1 && a.x2 <= b.x2 && a.y2 >= min(b.y1, b.y2)) {
        return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<palka> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        if (a[i].x1 > a[i].x2) {
            swap(a[i].x1, a[i].x2);
            swap(a[i].y1, a[i].y2);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            if (check(a[i], a[j])) {
                g[i].push_back(j);
            }
        }
    }
    /*for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            cout << i << " " << to << endl;
        }
    }*/
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << top_sort[i] + 1 << " ";
    }
    return 0;
}
