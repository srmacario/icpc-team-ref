
/**********************************************************************************
* IMPLICIT SEGMENT TREE (QUICK RANGE SUM / RANGE UPDATE)                          *
* Description: This segment tree is very similar to the normal one, but with a    *
* dynamic construction. The segment tree is being constructed at the time the     *
* updates are made. To build a initial tree, just read initial values and update. *
* Time complexity is based on Queries number, not on range updated.               *
* Range updated is define by the user, from a min to a max (min can be negative!) *
* Usage: update(1, min, max, pos, val), query(1, min, max, l, r)                  *
* Notation: st: array which stores the segment tree                               *
*           lc: array which stores the left child pointer                         *
*           lc: array which stores the right child pointer                        *
*           p: node index (NOT to confuse with the array index)                   *
**********************************************************************************/

/**********************************************************************************
* RANGE UPDATE VERSION (LAZY PROPAGATION)                                         *
**********************************************************************************/

const int N = 1e7+5;

int cnt = 1, st[N], lc[N], rc[N], lazy[N], n;

void push(int p, int l, int r){
    if(lazy[p]){
        st[p] += (r-l+1)*lazy[p];
            // RMQ (max/min)   -> update: = lazy[p],         incr: += lazy[p]
            // RSQ (sum)       -> update: = (r-l+1)*lazy[p], incr: += (r-l+1)*lazy[p]
            // Count lights on -> flip:   = (r-l+1)-st[p];
        if(l != r){
            if(lc[p]) lazy[lc[p]] += lazy[p];
            if(rc[p]) lazy[rc[p]] += lazy[p];
            // update:    lazy[2*p] = lazy[p],  lazy[2*p+1] = lazy[p];
            // increment: lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
            // flip:      lazy[2*p] ^= 1,       lazy[2*p+1] ^= 1;
        }
        lazy[p] = 0;
    }
}

void update(int p, int l, int r, int i, int j, int k){
    if(!p) return;
    if(!lc[p]) lc[p] = ++cnt;
    if(!rc[p]) rc[p] = ++cnt;
    push(p, l, r);
    if(r < i or j < l) return;
    if (i <= l and r <= j) {
        lazy[p] += k;
        // update:    lazy[p] = k;
        // increment: lazy[p] += k;
        // flip:      lazy[p] = 1;
        push(p, l, r);
        return;
    }
    int mid = (l+r)/2;
    update(lc[p],l,mid,i,j,k);
    update(rc[p],mid+1,r,i,j,k);
    st[p] = st[lc[p]] + st[rc[p]];
    //st[p] = min(st[2*p], st[2*p+1]);
    //st[p] = max(st[2*p], st[2*p+1]);
}

int query(int p, int l, int r, int i, int j){
    if(!p) return 0;
    // return INF;
    // return -INF;
    push(p,l,r);
    if(r < i or j < l) return 0;
    // return INF;
    // return -INF;
    if(i <= l and r <= j) return st[p];
    int mid = (l+r)/2;
    return query(lc[p], l, mid, i, j) + query(rc[p], mid+1, r, i, j);
    // return min(x, y);
    // return max(x, y);
}
