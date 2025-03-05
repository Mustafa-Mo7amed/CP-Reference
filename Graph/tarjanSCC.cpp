// 1-BASED
// n: number of nodes assuming they're numbered from [1:n]
// dfsn: is a dfs_number given to each node to check for back edges
// adj: adjacency list
// scc: stores all strongly connected components
// dag: is an adjacency list for a condensed graph (directed acyclic graph)
// dfs_num: stores dfsn for each node
// dfs_low: stores the lowest link (dfsn) the current node can reach
// compId: stores to what component each node belongs and giving them a unique id
// inStack: marks the current node that are in the current dfs path to check for cycles
int n, dfsn;
vector<vector<int>> adj, scc, dag;
vector<int> dfs_num, dfs_low, compId;
vector<bool> inStack;
stack<int> st;
void tarjan(int node) {
    dfs_num[node] = dfs_low[node] = dfsn++;
    inStack[node] = true;
    st.emplace(node);
    for (auto& child : adj[node]) {
        if (dfs_num[child] == -1) {
            tarjan(child);
            dfs_low[node] = min(dfs_low[node], dfs_low[child]);
        }
        else if (inStack[child])
            dfs_low[node] = min(dfs_low[node], dfs_num[child]);
    }
    // found a new SCC
    if (dfs_low[node] == dfs_num[node]) {
        scc.emplace_back();
        int x = -1;
        while (x != node) {
            x = st.top();
            st.pop();
            inStack[x] = false;
            compId[x] = (int) scc.size() - 1;
            scc.back().emplace_back(x);
        }
    }
}
// CHECK THE SIZE OF CONTAINERS
void buildSCC() {
    dfsn = 0;
    dfs_num = dfs_low = compId = vector<int>(n + 1, -1);
    inStack.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (dfs_num[i] == -1)
            tarjan(i);
    }
}
void buildDAG() {
    dag.assign(n + 1, vector<int>());
    for (int node = 1; node <= n; ++node) {
        for (auto& child : adj[node]) {
            if (compId[node] != compId[child])
                dag[compId[node]].emplace_back(compId[child]);
        }
    }
}