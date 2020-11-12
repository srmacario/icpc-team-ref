
/**********************************************************************************
* FAST MEDIAN (EVALUATE MEDIANS QUICKLY)                                          *
* Description: The Median's Bizu uses two priority queues or multisets to split a *
* sequence into two halves and recover the median value in O(1). (With multisets  *
* you can erase any element.)                                                     *
* Usage: query()                                                                  *
* Notation: l:    set of lower elements                                           *
*           u:    set of upper elements                                           *
**********************************************************************************/

multiset <int> l, u;

void adjust () {
    if (l.size() > u.size() + 1) {
        u.insert(*l.rbegin());
        l.erase(l.find(*l.rbegin()));
    } else if (u.size() > l.size()) {
        l.insert(*u.begin());
        u.erase(u.begin());
    }
}

void add (int x) {
    if (u.empty() or x < *u.begin()) l.insert(x);
    else                             u.insert(x);
    adjust();
}

void del (int x) {
    if      (l.count(x)) l.erase(l.find(x));
    else if (u.count(x)) u.erase(u.find(x));
    adjust();
}

int query () {
    if (u.size() > l.size()) return *u.begin();
    return *l.rbegin();

    // if (l.size() > u.size()) return *l.rbegin();
    // return (*u.begin() + *l.rbegin())/2.;

    // => Get average value if total # of elements is even. Remember to change
    // "int query" into "ld query".
}