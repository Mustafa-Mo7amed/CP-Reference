template<typename T>
class SparseTable {
    vector<vector<T>> table; // 0-based

    // merge function
    T merge(const T a, const T b) {}

    // faster than storing an array of logs
    int log2_floor(int i) { return i > 0 ? 31 - __builtin_clz(i) : -1; }
public:
    // building
    SparseTable(vector<T>& a) {
        int n = a.size();
        int logN = log2_floor(n);
        table.assign(logN + 1, vector<T>(n + 1));
        for (int i = 0; i < n; ++i)
            table[0][i] = a[i];
        for (int sz = 1; sz <= logN; ++sz)
            for (int i = 0; i + (1 << sz) <= n; ++i)
                table[sz][i] = merge(table[sz - 1][i], table[sz - 1][i + (1 << (sz - 1))]);
    }

    // O(1)
    T query(int l, int r) {
        int lg = log2_floor(r - l + 1);
        return merge(table[lg][l], table[lg][r - (1 << lg) + 1]);
    }

    // O(log(n))
    T queryNonOverlap(int l, int r) {
        T res;
        bool first = true;
        int log = table.size() - 1;
        for (int sz = log; sz >= 0; --sz) {
            if (l + (1 << sz) - 1 <= r) {
                if (first)
                    res = table[sz][l], first = false;
                else
                    res = merge(res, table[sz][l]);
                l += 1 << sz;
            }
        }
        return res;
    }
};
