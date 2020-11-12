/**********************************************************************************
* LCA (LOWEST COMMON ANCESTOR)                                                    *
* Description: Given a tree, the LCA of two vertices is the nearest common        *
* ancestor.                                                                       *
* Pre-processing: We first need to calculate the heights to the root, h[i], and   *
*                 every parent, anc[u][0]. A simple DFS can be used.              *
*                 Later, we will generate the other ancestors, knowing that the   *
*                 2^j-ancestor of u is the 2^j-1 ancestor of 2^j-1 ancestor of u. *
* Calculate LCA:  Step 1. If u and v have different heights, set u as the vertex  *
*                         of greatest height.                                     *
*                 Step 2. Move u upwards until h[u] = h[v].                       *
*                 Step 3. If u == v, we have the LCA already.                     *
*                 Step 4. If u != v, move u and v upwards, together, until their  *
*                         parents are the same.                                   *
*                 Step 5. This common parent is lca(u, v).                        *
* Time complexity: <O(VlogV), O(logV)>                                            *
* Usage: lca (u, v)                                                               *
* Notation: h[i]:        height of i, i.e. depth of i from the root               *
*           anc[i][j]:   2^j-ancestor of vertex i, i.e. u such that h[u]+2^j=h[i] *
*           mx[i][j]:    Max edge between i and its 2^j-ancestor                  *
**********************************************************************************/

const int N = 1e5+5;  // Max number of vertices
const int K = 20;     // Each 1e3 requires ~ 10 K
const int M = K+5;
int n;                // Number of vertices
vi adj[N];
int vis[N], h[N], anc[N][M];

void dfs (int u) {
    vis[u] = 1;
    for (auto v : adj[u]) if (!vis[v]) {
        h[v] = h[u]+1;
        anc[v][0] = u;
        dfs(v);
    }
}

void build () {
    anc[1][0] = 1;
    dfs(1);
    for (int j = 1; j <= K; j++) for (int i = 1; i <= n; i++)
        anc[i][j] = anc[anc[i][j-1]][j-1];
}

int lca (int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    for (int j = K; j >= 0; j--) if (h[anc[u][j]] >= h[v]) {
        u = anc[u][j];
    }
    if (u == v) return u;
    for (int j = K; j >= 0; j--) if (anc[u][j] != anc[v][j]) {
        u = anc[u][j];
        v = anc[v][j];
    }
    return anc[u][0];
}

int dist (int u, int v) {
    return h[u] + h[v] - 2*h[lca(u, v)];
}

// Using LCA to find max edge weight between (u, v)

const int N = 1e5+5;  // Max number of vertices
const int K = 20;     // Each 1e3 requires ~ 10 K
const int M = K+5;
int n;                // Number of vertices
vector <pii> adj[N];
int vis[N], h[N], anc[N][M], mx[N][M];

void dfs (int u) {
    vis[u] = 1;
    for (auto p : adj[u]) {
        int v = p.st;
        int w = p.nd;
        if (!vis[v]) {
            h[v] = h[u]+1;
            anc[v][0] = u;
            mx[v][0] = w;
            dfs(v);
        }
    }
}

void build () {
    // cl(mn, 63) -- Don't forget to initialize with INF if min edge!
    anc[1][0] = 1;
    dfs(1);
    for (int j = 1; j <= K; j++) for (int i = 1; i <= n; i++) {
        anc[i][j] = anc[anc[i][j-1]][j-1];
        mx[i][j] = max(mx[i][j-1], mx[anc[i][j-1]][j-1]);
    }
}

int mxedge (int u, int v) {
    int ans = 0;

    if (h[u] < h[v]) swap(u, v);
    for (int j = K; j >= 0; j--) if (h[anc[u][j]] >= h[v]) {
        ans = max(ans, mx[u][j]);
        u = anc[u][j];
    }
    if (u == v) return ans;
    for (int j = K; j >= 0; j--) if (anc[u][j] != anc[v][j]) {
        ans = max(ans, mx[u][j]);
        ans = max(ans, mx[v][j]);
        u = anc[u][j];
        v = anc[v][j];
    }
    return max({ans, mx[u][0], mx[v][0]});
}
