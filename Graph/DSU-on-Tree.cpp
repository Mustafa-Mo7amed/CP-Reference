// DSU on Tree (Small-to-Large) (Sack)
// 1) Define your data structures and global variables in the "// === User Data ===" section.
// 2) Implement the `update_node(int u, int delta)` function to update your DS state when adding/removing node u.
// 3) Call `pre()` from your main, after reading input and building the tree.

const int N = 1e5 + 5;

int n;
vector<int> adj[N];

int sz[N];          // subtree sizes
int big[N];         // index of big (heavy) child (or -1)

// update function
// Call this to add (delta = +1) or remove (delta = -1) the contribution
// of node `u`. Inside, update your DS data structures.
void update_node(int u, int delta) {
    // e.g.:
    // int col = color[u];
    // int oldf = freq[col];
    // // remove old contribution
    // sum[oldf] -= col;
    // freq[col] += delta;
    // int newf = freq[col];
    // sum[newf] += col;
    // // update current_max if needed:
    // if (newf > current_max) current_max = newf;
    // else if (sum[oldf] == 0 && oldf == current_max) --current_max;
}

// === Compute subtree sizes and identify big (heavy) child ===
void dfs_size(int u, int p) {
    sz[u] = 1;
    big[u] = -1;
    int maxSub = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_size(v, u);
        if (sz[v] > maxSub) {
            maxSub = sz[v];
            big[u] = v;
        }
        sz[u] += sz[v];
    }
}

// === Add or Remove a Whole Subtree ===
void add_subtree(int u, int p, int delta) {
    update_node(u, delta);
    for (int v : adj[u]) {
        if (v == p) continue;
        add_subtree(v, u, delta);
    }
}

// === DSU-on-Tree Main DFS ===
// `keep = true` to retain this subtree's contributions after return
void dfs_dsu(int u, int p, bool keep) {
    // process all light children and clear them
    for (int v : adj[u]) {
        if (v == p || v == big[u]) continue;
        dfs_dsu(v, u, false);
    }

    // process big child and keep its data
    if (big[u] != -1)
        dfs_dsu(big[u], u, true);

    // add current node and all light subtrees into big subtree's data
    update_node(u, +1);
    for (int v : adj[u]) {
        if (v == p || v == big[u]) continue;
        add_subtree(v, u, +1);
    }

    // === Here, DS state reflects u's entire subtree ===
    // Record the answer for node u, e.g.:
    // ans[u] = sum[current_max];

    // if not keeping, remove all contributions from this subtree
    if (!keep) {
        add_subtree(u, p, -1);
        // reset your DS state if necessary:
        // e.g. current_max = 0;
        //      fill(freq.begin(), freq.end(), 0);
        //      fill(sum.begin(), sum.end(), 0LL);
    }
}

void pre() {
    // 1) Read n, the tree edges, and user data (e.g., colors)
    // 2) Initialize user data structures (sizes, freq, sum, etc.)
    dfs_size(1, 0);
    dfs_dsu(1, 0, true);
}
