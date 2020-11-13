
/**********************************************************************************
* 2-SAT (TELL WHETHER A SERIES OF STATEMENTS CAN OR CANNOT BE FEASIBLE AT THE     *
* SAME TIME)                                                                      *
* Description: Given some p => q clauses, identify if it can be possibly true or  *
* not.                                                                            *
* Example: The series of statements "if monkeys are green then turtles are red"   *
* and "if monkeys are green then turtles are blue" is impossible to be satisfied, *
* i.e. there is no monkeys color and turtles color that ever turns all of them    *
* true. 2-SAT tells if there is a solution, and if true, shows it.                *
* Time complexity: O(V+E)                                                         *
* Usage: n         -> number of variables, 1-indexed                              *
*        p = v(i)  -> picks the "true" state for variable i                       *
*        p = nv(i) -> picks the "false" state for variable i, i.e. ~i             *
*        add(p, q) -> add clause p => q (which also means ~q => ~p)               *
*        run2sat() -> true if possible, false if impossible                       *
*        val[i]    -> tells if i has to be true or false for that solution        *
**********************************************************************************/

const int N = 1e5+5;

int n, vis[2*N], ord[2*N], ordn, cnt, cmp[2*N], val[N];
vector <int> adj[2*N], adjt[2*N];

// Maps every "true" state of it to 2*i and every "false" one (i.e. ~i) to 2*i+1.
int v (int x) { return 2*x; }
int nv (int x) { return 2*x+1; }

void add (int p, int q) {
    adj[p].push_back(q);
    adj[q^1].push_back(p^1);
    adjt[q].push_back(p);
    adjt[p^1].push_back(q^1);
}

void dfs (int x) {
    vis[x] = 1;
    for (auto v : adj[x]) if (!vis[v]) dfs(v);
    ord[ordn++] = x;
}

void dfst (int x) {
    cmp[x] = cnt, vis[x] = 0;
    for(auto v : adjt[x]) if (vis[v]) dfst(v);
}

bool run2sat() {
    for (int i = 1; i <= n; i++) {
        if (!vis[v(i)]) dfs(v(i));
        if (!vis[nv(i)]) dfs(nv(i));
    }
    for (int i = ordn-1; i >= 0; i--)
        if (vis[ord[i]]) cnt++, dfst(ord[i]);
    for (int i = 1; i <= n; i++) {
        if (cmp[v(i)] == cmp[nv(i)]) return false;
        val[i] = cmp[v(i)] > cmp[nv(i)];
    }
    return true;
}

int main () {
    for (int i = 1; i <= n; i++) {
        if (val[i]); // i-th variable is true
        else         // i-th variable is false
}