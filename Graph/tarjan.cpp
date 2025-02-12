vector<vector<int>> components; // stores all strongly connected components
// dfs_num: used as a visited array and it represents the dfs_number of nodes
// lowLink: represents the lowest dfs_number the current node can reach (ancestors would have lower dfs_number)
// compId: its indices represents nodes and the value represents the index of the component that this node belongs to in "components" vector
vector<int> dfs_num(n + 1, -1), low(n + 1), compId(n + 1);
vector<bool> inStack(n + 1); // marks the current path in dfs to detect cycles
stack<int> stk; // stores the nodes of the current connected component
int dfsn = 0; // marks each node with a dfs_number
function<void(int)> tarjan = [&](int node) {
    dfs_num[node] = low[node] = dfsn++;
    inStack[node] = true;
    stk.emplace(node);
    for (auto& i : adj[node]) {
        if (dfs_num[i] == -1) {
            tarjan(i);
            low[node] = min(low[node], low[i]);
        }
        else
            low[node] = min(low[node], dfs_num[i]);
    }
    inStack[node] = false;
    if (low[node] == dfs_num[node]) {
        int x = -1;
        components.emplace_back(); // pushing an empty vector
        while (x != node) { // till the root
            x = stk.top();
            stk.pop();
            inStack[x] = false;
            components.back().emplace_back(x);
            compId[x] = sz(components) - 1;
        }
    }
};
// graph condensation
vector<vector<int>> dagList(sz(components));
const auto computeCompGraph = [&]() {
    for (int node = 1; node < sz(adj); ++node) {
        for (auto& i : adj[node]) {
            if (compId[node] != compId[i])
                dagList[compId[node]].emplace_back(compId[i]);
        }
    }
};