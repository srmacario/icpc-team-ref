/**********************************************************************************
* BELLMAN-FORD ALGORITHM (SHORTEST PATH TO A VERTEX - WITH NEGATIVE COST)         *
* Description: Given any graph (not necessarily a tree), with no negative cycles, *
* the algorithm generates an array denoting the shortest distance from each       *
* vertex to the start point. It starts considering all distances equal to         *
* infinity and then uses the given edges in a for loop to generate the array.     *
* The Bellman-Ford Algorithm uses an array, dist[N], which begins with value 0    *
* assigned to dist[strt] and INF to every other one. Then, it iterates through    *
* all vertices, in increasing order, and tries to assign each dist[neighbor] as   *
* dist[vertex] + edge, but dist[vertex] might still be INF. (In fact, only the    *
* first vertex will have its neighbors evaluated in the first loop.) Thus, we     *
* have to repeat this process vert-1 times, because in the worst case all the     *
* vertices would be aligned.                                                      *
* Time complexity: O(VE)                                                          *
* Usage: dist[node]                                                               *
* Notation: m:           number of edges                                          *
*           n:           number of vertices                                       *
*           (a, b, w):   edge between a and b with weight w                       *
*           s:           starting node                                            *
**********************************************************************************/

const int N = 1e4+10; // Maximum number of nodes
int dist[N];
vector <pii> adj[N];
int a, b, w, s, m, n;

void bford () {
    // Be careful with directed graphs!
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        adj[a].pb({b, w}); // Be careful!
        adj[b].pb({a, w}); // Be careful!
    }

    cl(dist, 63);
    dist[s] = 0;

    for (int i = 0; i < n-1; i++)
        for (int u = 0; u < n; u++)
            for (auto x : adj[u]) {
                int v = x.st;
                int w = x.nd;
                dist[v] = min(dist[v], dist[u] + w);
            }
}
