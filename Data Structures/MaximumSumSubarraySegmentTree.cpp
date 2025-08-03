// implement your custom node
struct node {
    int sum, maxSeg, pre, suf;
    node() : sum(0), maxSeg(0), pre(0), suf(0) {}
    node(int val) : sum(val), maxSeg(val), pre(val), suf(val) {}
    node(int sum, int maxSeg, int pre, int suf) : sum(sum), maxSeg(maxSeg), pre(pre), suf(suf) {}
};
class SegmentTree { // 1-based
#define LEFT (idx << 1)
#define RIGHT (idx << 1 | 1)
#define MID ((start + end) >> 1)
    int n;

    // implement your custom merge
    node merge(const node l, const node r) {
        node cur;
        cur.sum = l.sum + r.sum;
        cur.maxSeg = max({l.maxSeg, r.maxSeg, l.suf + r.pre});
        cur.pre = max(l.pre, l.sum + r.pre);
        cur.suf = max(r.suf, r.sum + l.suf);
        return cur;
    }

    void build(int idx, int start, int end, const vector<int>& a) { // denote that the type of a is INT
        if (start == end) {
            tree[idx] = node(a[start]); // note: the index of a is START
            return;
        }
        build(LEFT, start, MID, a);
        build(RIGHT, MID + 1, end, a);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
    node query(int idx, int start, int end, int l, int r) {
        if (end < l || start > r)
            return node(); // return a neutral value that doesn't affect the query
        if (start >= l && end <= r)
            return tree[idx];
        return merge(query(LEFT, start, MID, l, r),
                       query(RIGHT, MID + 1, end, l, r));
    }
    void update(int idx, int start, int end, int index, int val) { // denote that the type of val is INT
        if (end < index || start > index)
            return;
        if (start == end && index == start) {
            tree[idx] = val; // update tree
            return;
        }
        update(LEFT, start, MID, index, val);
        update(RIGHT, MID + 1, end, index, val);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
public:
    vector<node> tree;
    SegmentTree(int n): n(n), tree(n << 2) {}
    SegmentTree(const vector<int>& v): n(v.size() - 1), tree(vector<node>(n << 2)) { // denote that the type of v is INT
        build(1, 1, n, v);
    }
    void update(int index, int val) {
        update(1, 1, n, index, val);
    }
    node query(int l, int r) {
        return query(1, 1, n, l, r);
    }
#undef LEFT
#undef RIGHT
#undef MID
};