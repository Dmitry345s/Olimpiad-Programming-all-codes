#include<bits/stdc++.h>

using namespace std;
using ll = long long;

int ans[50][50][12];

void c12(int u, int add) {
    for (int j = 0; j < u; ++j) {
        for (int k = 0; k < 12; ++k) {
            cout << j * 12 + k + add << " ";
        }
        cout << endl;
    }
}

void c6(int u, int add) {
    if (u < 2) return;
    for (int j = 0; j < u; ++j) {
        for (int j2 = j + 1; j2 < u; ++j2) {
            for (int k = 0; k < 6; ++k) {
                cout << j * 6 + k + add << " ";
            }
            for (int k = 0; k < 6; ++k) {
                cout << j2 * 6 + k + add << " ";
            }
            cout << endl;
        }
    }
}

void c4(int u, int add) {
    if (u < 3) return;
    for (int j = 0; j < u; ++j) {
        for (int j2 = j + 1; j2 < u; ++j2) {
            for (int j3 = j2 + 1; j3 < u; ++j3) {
                for (int k = 0; k < 4; ++k) {
                    cout << j * 4 + k + add << " ";
                }
                for (int k = 0; k < 4; ++k) {
                    cout << j2 * 4 + k + add << " ";
                }
                for (int k = 0; k < 4; ++k) {
                    cout << j3 * 4 + k + add << " ";
                }
                cout << endl;
            }
        }
    }
}

void c3(int u, int add) {
    if (u < 4) return;
    for (int j = 0; j < u; ++j) {
        for (int j2 = j + 1; j2 < u; ++j2) {
            for (int j3 = j2 + 1; j3 < u; ++j3) {
                for (int j4 = j3 + 1; j4 < u; ++j4) {
                    for (int k = 0; k < 3; ++k) {
                        cout << j * 3 + k + add << " ";
                    }
                    for (int k = 0; k < 3; ++k) {
                        cout << j2 * 3 + k + add << " ";
                    }
                    for (int k = 0; k < 3; ++k) {
                        cout << j3 * 3 + k + add << " ";
                    }
                    for (int k = 0; k < 3; ++k) {
                        cout << j4 * 3 + k + add << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
}

void c2(int u, int add) {
    if (u < 6) return;
    for (int j = 0; j < u; ++j) {
        for (int j2 = j + 1; j2 < u; ++j2) {
            for (int j3 = j2 + 1; j3 < u; ++j3) {
                for (int j4 = j3 + 1; j4 < u; ++j4) {
                    for (int j5 = j4 + 1; j5 < u; ++j5) {
                        for (int j6 = j5 + 1; j6 < u; ++j6) {
                            for (int k = 0; k < 2; ++k) {
                                cout << j * 2 + k + add << " ";
                            }
                            for (int k = 0; k < 2; ++k) {
                                cout << j2 * 2 + k + add << " ";
                            }
                            for (int k = 0; k < 2; ++k) {
                                cout << j3 * 2 + k + add << " ";
                            }
                            for (int k = 0; k < 2; ++k) {
                                cout << j4 * 2 + k + add << " ";
                            }
                            for (int k = 0; k < 2; ++k) {
                                cout << j5 * 2 + k + add << " ";
                            }
                            for (int k = 0; k < 2; ++k) {
                                cout << j6 * 2 + k + add << " ";
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
}

void c1(int u, int add) {
    if (u < 12) return;
    if (u == 12) {
        for (int j = 0; j < 12; ++j) {
            cout << j + add << " ";
        }
        cout << endl;
        return;
    }
    if (u == 13) {
        for (int j = 0; j < 13; ++j) {
            for (int k = 0; k < 12; ++k) {
                cout << (j + k) % 13 + add << " ";
            }
            cout << endl;
        }
        return;
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> cc[13];
    cc[12] = {0, 1, 2, 3, 4};
    cc[6] = {0, 0, 1, 3, 6, 10, 15, 21, 28};
    cc[4] = {0, 0, 0, 1, 4, 10, 20, 35};
    cc[3] = {0, 0, 0, 0, 1, 5, 15, 35};
    cc[2] = {0, 0, 0, 0, 0, 0, 1, 7, 28};
    cc[1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 13};
    for (int i12 = 0; i12 <= 4; ++i12) {
        for (int i6 = 0; i6 <= 8; ++i6) {
            for (int i4 = 0; i4 <= 7; ++i4) {
                for (int i3 = 0; i3 <= 7; ++i3) {
                    for (int i2 = 0; i2 <= 8; ++i2) {
                        for (int i1 = 0; i1 <= 13; ++i1) {
                            int cnt = i12 * 12 + i6 * 6 + i4 * 4 + i3 * 3 + i2 * 2 + i1 * 1;
                            if (cnt > 50) continue;
                            int sum = cc[12][i12] + cc[6][i6] + cc[4][i4] + cc[3][i3] + cc[2][i2] + cc[1][i1];
                            if (sum == n) {
                                //cout << i12 << " " << i6 << " " << i4 << " " << i3 << " " << i2 << endl;
                                c12(i12, 0);
                                c6(i6, i12 * 12);
                                c4(i4, i12 * 12 + i6 * 6);
                                c3(i3, i12 * 12 + i6 * 6 + i4 * 4);
                                c2(i2, i12 * 12 + i6 * 6 + i4 * 4 + i3 * 3);
                                c1(i1, i12 * 12 + i6 * 6 + i4 * 4 + i3 * 3 + i2 * 2);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

