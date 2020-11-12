/**********************************************************************************
* FLOYD-WARSHALL ALGORITHM (SHORTEST PATH TO ANY VERTEX)                          *
* Description: Given any graph (not necessarily a tree), the algorithm generates  *
* a matrix denoting the shortest distance between any two vertices. It starts     *
* considering all distances equal to infinity and then uses the given edges in a  *
* for loop to generate the array.                                                 *
* The Floyd Warshall Algorithm considers that, given that the shortest distance   *
* between vertices A and B is x and between B and C is y, then the shortest       *
* distance between A and C will be x+y if B is an intermediate vertex. Therefore, *
* the main idea is to iterate through all possible intermediate vertices k and,   *
* fixed such k, iterate through all possible pairs (i,j) and assign dist[i][j] as *
* x+y (i.e. dist[i][k] + dist[k][j]) whenever possible.                           *
* Time complexity: O(V^3)                                                         *
* Usage: dist[from][to]                                                           *
* Notation: m:           number of edges                                          *
*           n:           number of vertices                                       *
*           (a, b, w):   edge between a and b with weight w                       *
**********************************************************************************/

const int N = 1e4+10; // Maximum number of nodes
int dist[N][N];
int a, b, w, n, m;

void floyd () {
    cl(dist, 63);
    // Be careful with directed graphs!
    for (int i = 0; i < m; i++) {
        scanf(" %d%d%d" , &a, &b, &w);
        dist[a][b] = w; // Be careful!
        dist[b][a] = w; // Be careful!
    }
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    // Watch out for 0-indexed graphs!
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
}
