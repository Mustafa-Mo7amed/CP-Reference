struct node {
    int mn, mx, cnt;
    node() : mn(1e9), mx(-1e9), cnt(0) {}
    node(int x) : mn(x), mx(x), cnt(1) {}
    node(int mn, int mx, int cnt) : mn(mn), mx(mx), cnt(cnt) {}
};
struct segment_tree {
    vector<int> a;
    vector<node> seg;
    segment_tree(const vector<int> v) : a(v) {
        seg.resize(4 * sz(a));
    }
    node merge(node l, node r) {
        return {min(l.mn, r.mn), max(l.mx, r.mx), l.cnt + r.cnt};
    }
    void build(int i, int s, int e) {
        if (s == e) {
            seg[i] = node(a[s]);
            return;
        }
        build(i * 2, s, (s + e) / 2);
        build(i * 2 + 1, (s + e) / 2 + 1, e);
        seg[i] = merge(seg[i * 2], seg[i * 2 + 1]);
    }
    node query(int i, int s, int e, int l, int r, int k) {
        if (e < l || s > r || k >= seg[i].mx)
            return {};
        if (s >= l && e <= r && k < seg[i].mn)
            return seg[i];
        return merge(query(i * 2, s, (s + e) / 2, l, r, k), query(i * 2 + 1, (s + e) / 2 + 1, e, l, r, k));
    }
    void update(int i, int s, int e, int idx, int val) {
        if (idx < s || idx > e)
            return;
        if (idx == s && s == e) {
            a[s] = val;
            seg[i] = node(a[s]);
            return;
        }
        update(i * 2, s, (s + e) / 2, idx, val);
        update(i * 2 + 1, (s + e) / 2 + 1, e, idx, val);
        seg[i] = merge(seg[i * 2], seg[i * 2 + 1]);
    }
};