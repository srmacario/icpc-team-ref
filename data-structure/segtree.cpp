/**********************************************************************************
* SEGMENT TREE (QUICK RANGE SUM / RANGE UPDATE)                                   *
* Description: The segment tree stores subarray answers in a tree-like fashion,   *
* in such a way we can query and update ranges in O(logN) time.                   *
* Time complexity: <O(NlogN), O(logN)>                                            *
* Usage: update(1, 1, n, pos, val), query(1, 1, n, l, r), build(1, 1, n)          *
* Notation: st: array which stores the segment tree                               *
*           v: vector being represented in the segment tree                       *
*           p: node index (NOT to confuse with the array index)                   *
**********************************************************************************/

/****************************************************************
 * CF 242E - XOR on Segment                                     *
 * Query = simple sum | Range update = XOR with k               *
 * Solution: Build 20 segtrees, 1 for each bit, and the update  *
 * will be a flip of the interval if (1 << tree)&k              *
 * (Similar to lights problem, where you flip some ranges and   *
 * query the # of turned on lights.)                            *
 ***************************************************************/

int st[4*N], v[N];

void build (int p, int l, int r) {
    if (l == r) {st[p] = v[l]; return;}
    build (2*p, l, (l+r)/2);
    build (2*p+1, (l+r)/2+1, r);
    st[p] = st[2*p]+st[2*p+1];
    // st[p] = min(st[2*p], st[2*p+1]);
    // st[p] = max(st[2*p], st[2*p+1]);
}

int query (int p, int l, int r, int i, int j) {
    if (r < i or j < l) return 0;
    // return INF;
    // return -INF;
    if (i <= l and r <= j) return st[p];
    int x = query(2*p, l, (l+r)/2, i, j);
    int y = query(2*p+1, (l+r)/2+1, r, i, j);
    return x+y;
    // return min(x, y);
    // return max(x, y);
}

void update (int p, int l, int r, int x, int v) {
    if (x < l or r < x) return;
    if (l == r and l == x) {st[p] = v; return;}
    update (2*p, l, (l+r)/2, x, v);
    update (2*p+1, (l+r)/2+1, r, x, v);
    if (l != r) st[p] = st[2*p]+st[2*p+1];
    //st[p] = min(st[2*p], st[2*p+1]);
    //st[p] = max(st[2*p], st[2*p+1]);
}

/**********************************************************************************
* RANGE UPDATE VERSION (LAZY PROPAGATION)                                         *
**********************************************************************************/

int st[4*N], v[N], lazy[4*N];

void build (int p, int l, int r) {
    if (l == r) {st[p] = v[l]; return;}
    build (2*p, l, (l+r)/2);
    build (2*p+1, (l+r)/2+1, r);
    st[p] = st[2*p]+st[2*p+1];
    // st[p] = min(st[2*p], st[2*p+1]);
    // st[p] = max(st[2*p], st[2*p+1]);
}

void push (int p, int l, int r) {
    if (lazy[p]) {
        st[p] += (r-l+1)*lazy[p];
        // RMQ (max/min)   -> update: = lazy[p],         incr: += lazy[p]
        // RSQ (sum)       -> update: = (r-l+1)*lazy[p], incr: += (r-l+1)*lazy[p]
        // Count lights on -> flip:   = (r-l+1)-st[p];
        if (l != r) {
            lazy[2*p] += lazy[p];
            lazy[2*p+1] += lazy[p];
            // update:    lazy[2*p] = lazy[p],  lazy[2*p+1] = lazy[p];
            // increment: lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
            // flip:      lazy[2*p] ^= 1,       lazy[2*p+1] ^= 1;
        }
        lazy[p] = 0;
    }
}

int query (int p, int l, int r, int i, int j) {
    push(p, l, r);
    if (r < i or j < l) return 0;
    // return INF;
    // return -INF;
    if (i <= l and r <= j) return st[p];
    int x = query(2*p, l, (l+r)/2, i, j);
    int y = query(2*p+1, (l+r)/2+1, r, i, j);
    return x+y;
    // return min(x, y);
    // return max(x, y);
}

void update (int p, int l, int r, int i, int j, int k) {
    push(p, l, r);
    if (r < i or j < l) return;
    if (i <= l and r <= j) {
        lazy[p] += k;
        // update:    lazy[p] = k;
        // increment: lazy[p] += k;
        // flip:      lazy[p] = 1;
        push(p, l, r);
        return;
    }
    update(2*p, l, (l+r)/2, i, j, k);
    update(2*p+1, (l+r)/2+1, r, i, j, k);
    if (l != r) st[p] = st[2*p] + st[2*p+1];
    //st[p] = min(st[2*p], st[2*p+1]);
    //st[p] = max(st[2*p], st[2*p+1]);
}