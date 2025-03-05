struct DSU {
    vector<int> rank, parent, size;
    vector<vector<int>> component;
    int forests;

    DSU(int n) {
        size = rank = parent = vector<int>(n + 1, 1);
        component = vector<vector<int>>(n + 1);
        forests = n;
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            component[i].push_back(i);
        }
    }

    int find_set(int v) {
        return parent[v] = (parent[v] == v ? v : find_set(parent[v]));
    }

    void link(int par, int node) {
        parent[node] = par;
        size[par] += size[node];
        for (const int &it: component[node])
            component[par].push_back(it);
        component[node].clear();
        if (rank[par] == rank[node])
            rank[par]++;
        forests--;
    }

    bool union_sets(int v, int u) {
        v = find_set(v), u = find_set(u);
        if (v != u) {
            if (rank[v] < rank[u])
                swap(v, u);
            link(v, u);
        }
        return v != u;
    }

    bool same_set(int v, int u) {
        return find_set(v) == find_set(u);
    }

    int size_set(int v) {
        return size[find_set(v)];
    }

};