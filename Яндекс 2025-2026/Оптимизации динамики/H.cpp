#include<bits/stdc++.h>

//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

using namespace std;

const int MOD = 1e9 + 7;

struct Matrix {
    int n;
    vector<vector<int>> mt;
    Matrix(int n1 = 0) {
        n = n1;
        mt.resize(n);
        for (int i = 0; i < n; ++i) {
            mt[i].resize(n);
            mt[i][i] = 1;
        }
    }
};

Matrix operator + (Matrix a, Matrix b) {
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.n; ++j) {
            b.mt[i][j] += a.mt[i][j];
            if (b.mt[i][j] >= MOD) b.mt[i][j] -= MOD;
        }
    }
    return b;
}

Matrix operator * (Matrix a, Matrix b) {
    Matrix ans = Matrix(a.n);
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < a.n; ++j) {
            ans.mt[i][j] = 0;
            for (int k = 0; k < a.n; ++k) {
                ans.mt[i][j] += (1ll * a.mt[i][k] * b.mt[k][j]) % MOD;
                if (ans.mt[i][j] >= MOD) ans.mt[i][j] -= MOD;
            }
        }
    }
    return ans;
}

Matrix fpow(Matrix a, int x) {
    Matrix ans = Matrix(a.n);
    while (x) {
        if (x % 2) {
            ans = ans * a;
        }
        a = a * a;
        x /= 2;
    }
    return ans;
}

Matrix st, step;

Matrix go(int d) {
    return st * fpow(step, d);
}

Matrix to_ans(int d, int k) {
    int t = k / d;
    vector<Matrix> degs(29);
    vector<Matrix> jdeg(29);
    degs[0] = fpow(step, d);
    jdeg[0] = degs[0];
    for (int i = 1; i < 29; ++i) {
        if ((1 << i) > t) break;
        degs[i] = degs[i - 1] + jdeg[i - 1] * degs[i - 1];
        jdeg[i] = jdeg[i - 1] * jdeg[i - 1];
    }
    Matrix now = Matrix(step.n);
    Matrix ans = Matrix(step.n);
    for (int i = 0; i < step.n; ++i) {
        for (int j = 0; j < step.n; ++j) {
            ans.mt[i][j] = 0;
        }
    }
    for (int u = 28; u >= 0; --u) {
        if ((t >> u) & 1) {
            ans = (ans + now * degs[u]);
            now = now * jdeg[u];
        }
    }
    return st * ans;
}

signed main() {
    int n, m, d, k;
    cin >> n >> m >> d >> k;
    int u = n * 10;
    st = Matrix(u);
    for (int i = 0; i < u; ++i) {
        for (int j = 0; j < u; ++j) {
            if (i != 0) {
                st.mt[i][j] = 0;
            } else {
                if (j >= u - n) {
                    st.mt[i][j] = 1;
                } else {
                    st.mt[i][j] = 0;
                }
            }
        }
    }
    step = Matrix(u);
    for (int i = 0; i < u; ++i) {
        for (int j = 0; j < u; ++j) {
            step.mt[i][j] = 0;
        }
    }
    for (int i = 0; i < u - n; ++i) {
        step.mt[i][i + n] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        step.mt[b + u - n][(10 - t) * n + a] = 1;
        step.mt[a + u - n][(10 - t) * n + b] = 1;
    }
    Matrix ans = to_ans(d, k);
    int rans = 0;
    for (int j = u - n; j < u; ++j) {
        rans += ans.mt[0][j];
        if (rans >= MOD) rans -= MOD;
    }
    cout << rans << endl;
    return 0;
}
