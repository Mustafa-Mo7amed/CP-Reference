// 1-BASED
// n: number of nodes assuming they're numbered from [1:n]
// adj: adjacency list
// SCC: stores all strongly connected components
// dag: is an adjacency list for a condensed graph (directed acyclic graph)
// compId: stores to what component each node belongs and giving them a unique id
// vis: visited array used in dfs
// out in dfs: stores the topological sort in "order" vector and then stores each component in vector "comp"
vector<vector<int>> adj, dag, SCC;
vector<int> compId;
vector<bool> vis;
void dfs(int node, const vector<vector<int>>& adj, vector<int>& out) {
    vis[node] = true;
    for (auto& i : adj[node]) {
        if (!vis[i])
            dfs(i, adj, out);
    }
    out.emplace_back(node);
}
void buildSCC() {
    int n = (int)adj.size() - 1;

    // topological sort
    vector<int> order;
    vis.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i])
            dfs(i, adj, order);
    }

    // reversing graph
    vector<vector<int>> adj_rev(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (auto& j : adj[i])
            adj_rev[j].emplace_back(i);
    }

    // finding all connected components and marking each node with a component id
    reverse(all(order));
    vis.assign(n + 1, false);
    compId.assign(n + 1, 0);
    for (auto& i : order) {
        if (!vis[i]) {
            SCC.emplace_back();
            vector<int> comp;
            dfs(i, adj_rev, comp);
            for (auto& j : comp) {
                compId[j] = SCC.size() - 1;
                SCC.back().emplace_back(j);
            }
        }
    }
}
void buildDAG() {
    int n = adj.size() - 1;
    dag.assign(SCC.size(), {});
    for (int i = 1; i <= n; ++i) {
        for (auto& j : adj[i]) {
            if (compId[i] != compId[j])
                dag[compId[i]].emplace_back(compId[j]);
        }
    }
}