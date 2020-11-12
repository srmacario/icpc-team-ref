/**********************************************************************************
* DSU (DISJOINT SET UNION / UNION-FIND)                                           *
* Description: The DSU structure performs two operations: union and find. It is   *
* required in Kruskal's MST algorithm.                                            *
* FIND: Determine if two elements are in the same subset. Can be used to detect   *
* cycles in an undirected graph.                                                  *
* UNION: Join two subsets into a single subset.                                   *
* Usage: find(node), unite(node1, node2), sz[find(node)]                          *
* Notation: par: vector of parents                                                *
*           sz:  vector of subsets sizes, i.e. size of the subset a node is in    *
**********************************************************************************/

int par[N], sz[N];

int find (int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void unite (int a, int b) {
    if ((a = find(a)) == (b = find(b))) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    par[b] = a;
}

int main () {
    for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
}

// WITH PARTIAL PERSISTENCE
// his: history: time when it got a new parent
// t: current time

int t, par[N], sz[N], his[N];

int find (int a, int t){
    if (par[a] == a) return a;
    if (his[a] > t) return a;
    return find(par[a], t);
}

void unite (int a, int b){
    if (find(a, t) == find(b, t)) return;
    a = find(a, t), b = find(b, t), t++;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    par[b] = a;
    his[b] = t;
}

int main () {
    for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1, his[i] = 0;
}

// WITH ROLLBACK
// Undo last operation

int par[N], sz[N];
stack <pii> sp, ss;

int find (int a) { return par[a] == a ? a : find(par[a]); }

void unite (int a, int b) {
    if ((a = find(a)) == (b = find(b))) return;
    if (sz[a] < sz[b]) swap(a, b);
    ss.push({a, sz[a]});
    sp.push({b, par[b]});
    sz[a] += sz[b];
    par[b] = a;
}

void rollback() {
    par[sp.top().st] = sp.top().nd; sp.pop();
    sz[ss.top().st]  = ss.top().nd; ss.pop();
}

int main () {
    for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
}
