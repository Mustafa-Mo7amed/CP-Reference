bool bccRoot = false; // if the root of the dfs has more than one BCC then true, otherwise false
vector<bool> articulation_points(n + 1); // marks all articulation points
vector<vector<pair<int, int>>> BCC; // stores all biconnected components
stack<pair<int, int>> bccEdges; // stores the current biconnected component till it's pushed into "BCC" vector
vector<vector<int>> SCC; // stores all strongly connected components
// dfs_num: used as a visited array and it represents the dfs_number of nodes
// lowLink: represents the lowest dfs_number the current node can reach (ancestors would have lower dfs_number)
// compId: its indices represents nodes and the value represents the index of the component that this node belongs to in "components" vector
vector<int> dfs_num(n + 1, -1), lowLink(n + 1), compId(n + 1);
vector<bool> inStack(n + 1); // marks the current path in dfs to detect cycles
set<pair<int, int>> bridges; // stores all bridges
stack<int> stk; // stores the nodes of the current connected component
int dfsn = 0; // marks each node with a dfs_number
function<void(int, int)> tarjan = [&](int node, int par) {
    dfs_num[node] = lowLink[node] = dfsn++;
    inStack[node] = true;
    stk.emplace(node);
    for (auto& child : adj[node]) {
        if (child != par && dfs_num[child] < dfs_num[node])
            bccEdges.emplace(node, child);
        if (dfs_num[child] == -1) {
            tarjan(child, node);
            lowLink[node] = min(lowLink[node], lowLink[child]);
            if (lowLink[child] >= dfs_num[node]) {
                if (dfs_num[node] == 0 && !bccRoot)
                    bccRoot = true;
                else
                    articulation_points[node] = true;
                BCC.emplace_back();
                pair<int, int> edge;
                do {
                    edge = bccEdges.top();
                    bccEdges.pop();
                    BCC.back().emplace_back(edge);
                } while (node != edge.first || edge.second != child);
            }
        }
        else if (child != par)
            lowLink[node] = min(lowLink[node], dfs_num[child]);
    }
    inStack[node] = false;
    if (lowLink[node] == dfs_num[node]) {
        if (par != -1)
            bridges.emplace(par, node);
        int x = -1;
        SCC.emplace_back(); // pushing an empty vector
        while (x != node) { // till the root
            x = stk.top();
            stk.pop();
            inStack[x] = false;
            SCC.back().emplace_back(x);
            compId[x] = sz(SCC) - 1;
        }
    }
};
// graph condensation
vector<vector<int>> dagList(sz(SCC));
const auto computeCompGraph = [&]() {
    for (int node = 1; node < sz(adj); ++node) {
        for (auto& i : adj[node]) {
            if (compId[node] != compId[i])
                dagList[compId[node]].emplace_back(compId[i]);
        }
    }
};