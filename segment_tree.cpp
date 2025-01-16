template<typename T>
class segment_tree { //1-based
#define LEFT (idx << 1)
#define RIGHT (idx << 1 | 1)
#define MID ((start + end) >> 1)
    int n;
    vector<T> tree, lazy;
    T merge(const T& left, const T& right) {}
    void pushdown(int idx, int start, int end) {
        if (lazy[idx] == 0)
            return;
        // update tree[idx] with lazy[idx]
        tree[idx] += lazy[idx];
        if (start != end) {
            lazy[LEFT] += lazy[idx];
            lazy[RIGHT] += lazy[idx];
        }
        lazy[idx] = 0; //clear lazy
    }
    void build(int idx, int start, int end) {
        if (start == end)
            return;
        build(LEFT, start, MID);
        build(RIGHT, MID + 1, end);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
    void build(int idx, int start, int end, const vector<T>& arr) {
        if (start == end) {
            tree[idx] = arr[start];
            return;
        }
        build(LEFT, start, MID, arr);
        build(RIGHT, MID + 1, end, arr);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
    T query(int idx, int start, int end, int from, int to) {
        pushdown(idx, start, end);
        if (from <= start && end <= to)
            return tree[idx];
        if (to <= MID)
            return query(LEFT, start, MID, from, to);
        if (MID < from)
            return query(RIGHT, MID + 1, end, from, to);
        return merge(query(LEFT, start, MID, from, to),
                     query(RIGHT, MID + 1, end, from, to));
    }
    void update(int idx, int start, int end, int l, int r, const T& val) {
        pushdown(idx, start, end);
        if (r < start || end < l)
            return;
        if (l <= start && end <= r) {
            lazy[idx] += val; //update lazy
            pushdown(idx, start, end);
            return;
        }
        update(LEFT, start, MID, l, r, val);
        update(RIGHT, MID + 1, end, l, r, val);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
public:
    segment_tree(int n) : n(n), tree(n << 2), lazy(n << 2) {}
    segment_tree(const vector<T>& v) {
        n = v.size() - 1;
        tree = vector<T>(n << 2);
        lazy = vector<T>(n << 2);
        build(1, 1, n, v);
    }
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    void update(int l, int r, const T& val) {
        update(1, 1, n, l, r, val);
    }
#undef LEFT
#undef RIGHT
#undef MID
};