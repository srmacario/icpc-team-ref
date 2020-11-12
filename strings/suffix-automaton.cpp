/**********************************************************************************
* SUFFIX AUTOMATON (THE KING OF SUFFIXES!)                                        *
* Description: A suffix automaton is a trie with all the suffixes of a word.      *
*              Please refer to Trie section for more information about tries.     *
* Time complexity: O(N)                                                           *
* Notation: adj[u][v]:  means we have u -> v edge in the trie (rooted at u = 0)   *
**********************************************************************************/

const int N = 1e6+1, K = 26;

int sl[2*N], len[2*N], sz, last;
ll cnt[2*N];
map <int, int> adj[2*N];

void add (int c) {
    int u = sz++;
    len[u] = len[last] + 1;
    cnt[u] = 1;

    int p = last;
    while (p != -1 and !adj[p][c]) {
        adj[p][c] = u;
        p = sl[p];
    }

    if (p == -1) sl[u] = 0;
    else {
        int q = adj[p][c];
        if (len[p]+1 == len[q]) sl[u] = q;
        else {
            int r = sz++;
            len[r] = len[p]+1;
            sl[r] = sl[q];
            adj[r] = adj[q];
            while (p != -1 and adj[p][c] == q) {
                adj[p][c] = r;
                p = sl[p];
            }
            sl[q] = sl[u] = r;
        }
    }

    last = u;
}

void clear() {
    for(int i = 0; i <= sz; ++i) adj[i].clear();
    last = 0;
    sz = 1;
    sl[0] = -1;
}

void build (string& s) {
    clear();
    for (auto c : s) add(c);
}

// Pattern matching - O(|p|)
bool check (string& p) {
    int u = 0, ok = 1;
    for (auto c : p) {
        u = adj[u][c];
        if (!u) ok = 0;
    }
    return ok;
}

// Substring count - O(|p|)
ll d[2*N];

void substr_cnt(int u) {
    d[u] = 1;
    for (auto p : adj[u]) {
        int v = p.second;
        if (!d[v]) substr_cnt(v);
        d[u] += d[v];
    }
}

ll substr_cnt() {
    memset(d, 0, sizeof d);
    substr_cnt(0);
    return d[0] - 1;
}

// k-th Substring - O(|s|)
// Just find the k-th path in the automaton.
// Can be done with the value d calculated in previous problem.

// Smallest cyclic shift - O(|s|)
// Build the automaton for string s + s. And adapt previous dp
// to only count paths with size |s|.


// Number of occurences - O(|p|)
vector<int> t[2*N];

void occur_count (int u) {
    for (int v : t[u]) occur_count(v), cnt[u] += cnt[v];
}

void build_tree() {
    for (int i = 1; i <= sz; ++i)
        t[sl[i]].push_back(i);
    occur_count(0);
}

ll occur_count (string& p) {
    // Call build tree once per automaton
    int u = 0;
    for (auto c : p) {
        u = adj[u][c];
        if (!u) break;
    }
    return !u ? 0 : cnt[u];
}

// First occurence - (|p|)
// Store the first position of occurence fp.
// Add the the code to add function:
// fp[u] = len[u] - 1;
// fp[r] = fp[q];

// To answer a query, just output fp[u] - strlen(p) + 1
// where u is the state corresponding to string p

// All occurences - O(|p| + |ans|)
// All the occurences can reach the first occurence via suffix links.
// So every state that contains a occreunce is reacheable by the
// first occurence state in the suffix link tree. Just do a DFS in this
// tree, starting from the first occurence.
// OBS: cloned nodes will output same answer twice.


// Smallest substring not contained in the string - O(|s| * K)
// Just do a dynamic programming:
// d[u] = 1 // if d does not have 1 transition
// d[u] = 1 + min d[v] // otherwise


// LCS of 2 Strings - O(|s| + |t|)
// Build automaton of s and traverse the automaton with string t
// mantaining the current state and the current length.
// When we have a transition: update state, increase length by one.
// If we don't update state by suffix link and the new length
// should be reduced (if bigger) to the new state length.
// Answer will be the maximum length of the whole traversal.

// LCS of n Strings - O(n*|s|*K)
// Create a new string S = s_1 + d1 + ... + s_n + d_n,
// where d_i are delimiters that are unique (d_i != d_j).
// For each state use DP + bitmask to calculate if it can
// reach a d_i transition without going through other d_j.
// The answer will be the biggest len[u] that can reach all
// d_i's.
