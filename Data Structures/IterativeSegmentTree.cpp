// IMPLEMENT YOUR CUSTOM NODE
struct node {
    long long sum; // carful of overflows
    // Identity element's constructor (should not affect merge)
    node() : sum(0) {}
    node(long long val) : sum(val) {}
};
class SegmentTree {
    int n;
    std::vector<node> tree;

    // IMPLEMENT YOUR CUSTOM MERGE LOGIC
    node merge(const node& a, const node& b) {}


    // Internal build function using a 1-based source array
    void build(const std::vector<int>& arr) {
        // arr is 1-based, so its size is n+1
        // We map 1-based array index `i` to 0-based tree leaf `i-1`
        for (int i = 1; i <= n; ++i) {
            tree[n + i - 1] = node(arr[i]);
        }
        // Build the rest of the tree
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }
public:
    SegmentTree(int size) : n(size), tree(2 * n) {}
    SegmentTree(const std::vector<int>& v) : n(v.size() - 1), tree(2 * n) {
        build(v);
    }
    void update(int pos, int value) {
        pos = pos + n - 1;
        tree[pos] = node(value);
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }
    node query(int l, int r) {
        l--;
        node res_l, res_r;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res_l = merge(res_l, tree[l++]);
            if (r & 1)
                res_r = merge(tree[--r], res_r);
        }
        return merge(res_l, res_r);
    }
};