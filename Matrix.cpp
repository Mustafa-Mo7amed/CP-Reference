const int N = 100, mod = 1e9 + 7;
struct Matrix {
    int m[N][N]{};
    Matrix() = default;
    Matrix(int a[N][N]) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                m[i][j] = a[i][j];
    }
    Matrix operator*(const Matrix& other) const {
        Matrix ret;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    ret.m[i][j] += 1LL * m[i][k] * other.m[k][j] % mod;
                    if (ret.m[i][j] >= mod)
                        ret.m[i][j] -= mod;
                }
            }
        }
        return ret;
    }
    void identity() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                m[i][j] = i == j ? 1 : 0;
    }
};
Matrix power(Matrix m, ll p) {
    Matrix res;
    res.identity();
    while (p) {
        if (p & 1)
            res = res * m;
        m = m * m;
        p >>= 1;
    }
    return res;
}