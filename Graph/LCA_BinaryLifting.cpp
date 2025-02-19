struct LCA {
    int LOG;
    vector<int> depth;
    vector<vector<int>> adj, up;
    LCA(const vector<vector<int>>& _adj, const int root) : adj(_adj) { // O(n * log(n))
        int n = adj.size();
        LOG = 32 - __builtin_clz(n);
        up.assign(LOG + 1, vector<int>(n, -1));
        depth.resize(n);
        dfs(root, -1);
        for (int k = 1; k <= LOG; ++k) {
            for (int i = 0; i < n; ++i) {
                if (up[k - 1][i] == -1)
                    continue;
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }
    }
    void dfs(int node, int par) {
        up[0][node] = par;
        for (auto& i : adj[node]) {
            if (i == par)
                continue;
            depth[i] = depth[node] + 1;
            dfs(i, node);
        }
    }
    int lca(int u, int v) { // O(log(n))
        if (depth[u] < depth[v])
            swap(u, v);
        for (int k = LOG; k >= 0; --k) {
            if (depth[u] - (1 << k) >= depth[v])
                u = up[k][u];
        }
        if (u == v)
            return u;
        for (int k = LOG; k >= 0; --k) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    }
};