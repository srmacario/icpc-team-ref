/**********************************************************************************
* KUHN'S ALGORITHM (FIND GREATEST NUMBER OF MATCHINGS - BIPARTITE GRAPH)          *
* Description: Given a bipartite graph, find the greatest number of matchings     *
* such that each vertex of a partition is connected to at most one vertex of the  *
* other partition.                                                                *
* Time complexity: O(VE)                                                          *
* Notation: ans:      number of matchings                                         *
*           b[j]:     matching edge b[j] <-> j                                    *
*           adj[i]:   adjacency list for node i                                   *
*           vis:      visited nodes                                               *
*           x:        counter to help reuse vis list                              *
**********************************************************************************/

vi adj[N];
int x, b[N], vis[N], ans;

bool match (int u) {
    if (vis[u] == x) return 0;
    vis[u] = x;
    for (auto v : adj[u])
        if (!b[v] or match(b[v])) return b[v] = u;
    return 0;
}

int main () {
    for (int i = 1; i <= n; i++) x++, ans += match(i);
}

// Maximum Independent Set on bipartite graph
MIS + MCBM = V

// Minimum Vertex Cover on bipartite graph
MVC = MCBM
