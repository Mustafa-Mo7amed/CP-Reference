#include <bits/stdc++.h>
#define int long long
#define OO 0x3f3f3f3f3f3f3f3fLL
using namespace std;
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n + 1, vector<int>(n + 1, OO));
	for (int i = 1; i <= n; i++)
		adj[i][i] = 0; // do not initialize if there are negative values (self loops may lower the cost)
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u][v] = w;
		adj[v][u] = w;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (adj[i][k] < OO && adj[k][j] < OO) // condition could be omitted if 2 * OO fits in the current data type
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
	return 0;
}