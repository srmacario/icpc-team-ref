
/**********************************************************************************
* RABIN-KARP (STRING MATCHING + HASHING)                                          *
* Time complexity: O(N+M)                                                         *
* Notation: s:   main string                                                      *
*           p:   substring to be found                                            *
*           n:   s length                                                         *
*           m:   p length                                                         *
**********************************************************************************/

const int B = 31;
const int MOD = 1e9+7; // set mod
string s, p;

void rabin() {
    int n = s.size();
    int m = p.size();
    if (n < m) return;

    unsigned long long hp = 0, hs = 0, E = 1;
    for (int i = 0; i < m; i++) {
        hp = ((hp*B)%MOD + p[i])%MOD;
        hs = ((hs*B)%MOD + s[i])%MOD;
        E = (E*B)%MOD;
    }

    if (hs == hp) { /* matching position 0 (+1?) */ }
    for (int i = m; i < n; i++) {
        hs = ((hs*B)%MOD + s[i])%MOD;
        hs = (hs - s[i-m]*E%MOD + MOD)%MOD;
        if (hs == hp) { /* matching position i-m+1 (+1?) */ }
    }
}