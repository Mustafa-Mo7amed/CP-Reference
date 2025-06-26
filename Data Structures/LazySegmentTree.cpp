// implement your custom node
struct node {
    int cnt;
    node(): cnt(0) {} // don't forget to set your neutral value correctly
    node(int p): cnt(p) {}
};
class SegmentTree { // 1-based
#define LEFT (idx << 1)
#define RIGHT (idx << 1 | 1)
#define MID ((start + end) >> 1)
    int n;
    vector<node> tree;
    vector<int> lazy;

    // implement your custom merge
    node merge(const node l, const node r) {}
    
    void push(int idx, int start, int end) {
        if (lazy[idx] == 0) // not visited
            return;
        // update tree with lazy
        tree[idx] += lazy[idx];
        if (start != end) { // update lazy children
            lazy[LEFT] = lazy[idx];
            lazy[RIGHT] = lazy[idx];
        }
        lazy[idx] = 0; // clear lazy
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
        push(idx, start, end);
        if (end < l || start > r)
            return node(); // return a neutral value that doesn't affect the query
        if (start >= l && end <= r)
            return tree[idx];
        return merge(query(LEFT, start, MID, l, r),
                       query(RIGHT, MID + 1, end, l, r));
    }
    void update(int idx, int start, int end, int l, int r, int val) { // denote that the type of val is INT
        push(idx, start, end); // propagate
        if (end < l || start > r)
            return;
        if (start >= l && end <= r) {
            lazy[idx] = val; // update lazy
            push(idx, start, end); // propagate
            return;
        }
        update(LEFT, start, MID, l, r, val);
        update(RIGHT, MID + 1, end, l, r, val);
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }
public:
    SegmentTree(int n): n(n), tree(n << 2), lazy(n << 2) {}
    SegmentTree(const vector<int>& v) { // denote that the type of v is INT
        n = v.size() - 1;
        tree = vector<node>(n << 2);
        lazy = vector<int>(n << 2);
        build(1, 1, n, v);
    }
    void update(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }
    node query(int l, int r) {
        return query(1, 1, n, l, r);
    }
#undef LEFT
#undef RIGHT
#undef MID
};