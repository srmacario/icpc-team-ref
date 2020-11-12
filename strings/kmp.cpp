**********************************************************************************
* KMP (KNUTH-MORRIS-PRATT - STRING MATCHING)                                      *
* Time complexity: O(N+M)                                                         *
* Notation: s:   main string                                                      *
*           p:   substring to be found                                            *
*           n:   s length                                                         *
*           m:   p length                                                         *
**********************************************************************************/

string s, p;
int b[N], n, m;

void kmppre() {
    m = p.size();

    b[0] = -1;
    for (int i = 0, j = -1; i < m; b[++i] = ++j)
        while (j >= 0 and p[i] != p[j])
            j = b[j];
}

void kmp() {
    n = s.size();
    for (int i = 0, j = 0; i < n;) {
        while (j >= 0 and s[i] != p[j]) j = b[j];
        i++, j++;
        if (j == m) {
            // matching position i-m (+1?)
            j = b[j];
        }
    }
}
