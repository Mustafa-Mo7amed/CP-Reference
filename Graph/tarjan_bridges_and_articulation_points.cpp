// 1-BASED
// n: number of nodes assuming they're numbered from [1:n]
// dfsn: is a dfs_number given to each node to check for back edges
// adj: adjacency list
// dfs_num: stores dfsn for each node
// dfs_low: stores the lowest link (dfsn) the current node can reach
// stores all bridges
// markes all articulation points
int n, dfsn, cntChild;
vector<vector<int>> adj;
vector<int> dfs_num, dfs_low;
set<pair<int, int>> bridges;
vector<bool> articulation_points;
void tarjan(int node, int par) {
    dfs_num[node] = dfs_low[node] = dfsn++;
    for (auto& child : adj[node]) {
        if (child == par)
            continue;
        if (dfs_num[child] == -1) {
            if (par == -1)
                ++cntChild;
            tarjan(child, node);
            dfs_low[node] = min(dfs_low[node], dfs_low[child]);
            if (dfs_low[child] >= dfs_num[node])
                articulation_points[node] = true;
            if (dfs_low[child] > dfs_num[node])
                bridges.emplace(node, child);
        }
        else
            dfs_low[node] = min(dfs_low[node], dfs_num[child]);
    }
}
// CHECK THE SIZE OF CONTAINERS
void build_bridges_and_articulation_points() {
    dfsn = cntChild = 0;
    dfs_num = dfs_low = vector<int>(n + 1, -1);
    articulation_points.assign(n + 1, false);
    bridges.clear();
    for (int i = 1; i <= n; ++i) {
        if (dfs_num[i] == -1) {
            cntChild = 0;
            tarjan(i, -1);
            articulation_points[i] = cntChild > 1;
        }
    }
}