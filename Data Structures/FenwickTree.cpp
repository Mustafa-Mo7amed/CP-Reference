// 1-based
// range sum/update queries
class FenwickTree {
private:
    int n;
    std::vector<long long> tree;
    void add(int pos, long long delta) {
        for (; pos <= n; pos += pos & -pos) tree[pos] += delta;
    }
    long long prefix_query(int pos) {
        long long sum = 0;
        for (; pos > 0; pos -= pos & -pos) sum += tree[pos];
        return sum;
    }
public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}
    FenwickTree(const std::vector<int>& v) : n(v.size() - 1), tree(n + 1, 0) {
        for (int i = 1; i <= n; ++i) add(i, v[i]);
    }
    long long query(int l, int r) {
        if (l > r) return 0;
        return prefix_query(r) - prefix_query(l - 1);
    }
    long long get(int pos) {
        return query(pos, pos);
    }
    void update(int pos, long long new_val) {
        long long old_val = get(pos);
        long long delta = new_val - old_val;
        add(pos, delta);
    }
};