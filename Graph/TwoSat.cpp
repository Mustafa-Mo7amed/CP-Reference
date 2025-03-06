// 0-BASED
// adj: adjacency list for the implication graph
// adj_rev: reverse the adj for kosaraju's algorithm
// vis: marks visited vertices in dfs1
// order: stores the vertices in topological order
// compId: gives each vertex a unique id -> used to tell if x and ~x are in the same SCC
// also used to check whether x could reach ~x or not using compId[x] > compId[~x] then we set assignment[x] = true as we could imply ~x to x if x is true then ~x is false (false --> true is correct while true --> false is not)
// assignment: stores the answer of the TwoSat
struct TwoSat {
    int n_vars, n_vertices;
    vector<vector<int>> adj, adj_rev;
    vector<bool> vis;
    vector<int> order, compId;
    vector<bool> assignment;
    TwoSat(int vars): n_vars(vars), n_vertices(2 * vars), adj(n_vertices), adj_rev(n_vertices), vis(n_vertices), compId(n_vertices), assignment(vars) {
        order.reserve(n_vertices); // reserving memory to avoid reallocation when pushing elements into "order" vector
    }
    // topological sort
    void dfs1(int node) {
        vis[node] = true;
        for (auto& child : adj[node]) {
            if (!vis[child])
                dfs1(child);
        }
        order.emplace_back(node);
    }
    // marking each SCC with a unique id
    void dfs2(int node, int id) {
        compId[node] = id;
        for (auto& child : adj_rev[node]) {
            if (compId[child] == -1)
                dfs2(child, id);
        }
    }
    bool solve_2SAT() {
        order.clear();
        vis.assign(n_vertices, false);
        for (int i = 0; i < n_vertices; ++i) {
            if (!vis[i])
                dfs1(i);
        }
        compId.assign(n_vertices, -1);
        for (int i = n_vertices - 1, id = 0; i >= 0; --i) {
            int node = order[i];
            if (compId[node] == -1)
                dfs2(node, id++);
        }
        assignment.assign(n_vars, false);
        for (int i = 0; i < n_vertices; i += 2) {
            if (compId[i] == compId[i + 1]) // if x and ~x are in the same SCC then there's no possible solution
                return false;
            assignment[i / 2] = compId[i] > compId[i + 1]; // if x is reachable from ~x then set x to true (~x is false and false --> true is correct and true --> false is not) otherwise leave it as is
        }
        return true;
    }
    // a is the vertex and boolean na tells whether to negate the vertex or not, same for b
    // representing each vertex x as 2*x and its negation as 2*x+1
    // XOR flips the last bit to determine whether the vertex to be negated or not
    void add_disjunction(int a, bool na, int b, bool nb) {
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        // implication graph
        adj[neg_a].emplace_back(b);
        adj[neg_b].emplace_back(a);
        // reverse implication graph for kosaraju's algorigthm
        adj_rev[b].emplace_back(neg_a);
        adj_rev[a].emplace_back(neg_b);
    }
};