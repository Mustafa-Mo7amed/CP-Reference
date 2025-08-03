struct edge {
	int from, to, w;
	edge(int from, int to, int w) : from(from), to(to), w(w) {}
	bool operator<(edge other) const { return w > other.w; }
};
struct DSU {
	int forests;
	vector<int> parent, sz;
	explicit DSU(int n) {
		forests = n;
		parent = sz = vector<int>(n + 1);
		for (int i = 1; i <= n; i++)
			parent[i] = i, sz[i] = 1;
	}
	int find(int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}
	void uni(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
			return;
		if (sz[x] < sz[y])
			swap(x, y);
		parent[y] = x;
		sz[x] += sz[y];
		forests--;
	}
	vector<vector<int>> connected_components() {
		vector<vector<int>> list(sz(parent));
		for (int i = 1; i < sz(parent); i++)
			list[find(i)].emplace_back(i);
		return list;
	}
};
pair<int, vector<edge>> Kruskal_MST(vector<edge> edgeList, int n) {
	DSU dsu(n);
	vector<edge> edges;
	int mstCost = 0;
	priority_queue<edge> q;
	for (auto& i : edgeList)
		q.emplace(i);
	while (!q.empty()) {
		edge e = q.top();
		q.pop();
		if (dsu.find(e.from) != dsu.find(e.to)) {
			dsu.uni(e.from, e.to);
			edges.emplace_back(e);
			mstCost += e.w;
		}
	}
	if (sz(edges) != n - 1)
		return pair<int, vector<edge>>{ -OO, vector<edge>() };
	return { mstCost, edges };
}