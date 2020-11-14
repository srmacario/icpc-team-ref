/**********************************************************************************
* CHINESE REMAINDER THEOREM (SOLVES SYSTEMS OF CONGRUENCE EQUATIONS)              *
* Description: Consider the system of congruences:                                *
* x = a1 (mod p1)                                                                 *
* x = a2 (mod p2)                                                                 *
*     ...                                                                         *
* x = an (mod pn)                                                                 *
*                                                                                 *
* With the Chinese Remainder Theorem, we can solve the system two by two and find *
* x that solves all congruences. In each step, it will return a solution modulo   *
* lcm(p1, p2) = p1*p2/gcd(p1, p2). Note that p1, p2 do not need to be pairwise    *
* coprime. There may not be a solution, in which case hasSolution = false.        *
* Usage:    ll x = chinese(a, p, b, q)                                            *
* Notation: A, P: parameters of the final result x = A mod P                      *
**********************************************************************************/

const int N = 1e3+5; // max number of equations

void extgcd (ll a, ll b, ll &x, ll &y, ll &d) {
    if (b) extgcd(b, a%b, y, x, d), y -= x*(a/b);
    else x = 1, y = 0, d = a;
}

ll lcm (ll a, ll b) { return (a/gcd(a,b))*b; }

ll chinese (ll a, ll m, ll b, ll n) {
    ll u, v, g, mod = m*n;
    extgcd(m, n, u, v, g);
    return (((a*(v*n%mod) + b*(u*m%mod) % mod) + mod) % mod)/gcd(m, n);
}

// Below: How to solve a system with more than 2 equations

ll a[N], p[N];

int main () {
    int n = 5; // number of equations

    a[0] = 2, p[0] = 3;
    a[1] = 3, p[1] = 5;
    a[2] = 2, p[2] = 7;
    a[3] = 5, p[3] = 6;
    a[4] = 3, p[4] = 10;

    ll A = a[0], P = p[0];

    bool hasSolution = true;
    for (int i = 1; i < n; i++) {
        ll g = gcd(p[i], P);
        if (a[i] % g != A % g) hasSolution = false;
        A = chinese(a[i], p[i], A, P);
        P = lcm(p[i], P);
        A = (A+P)%P;
    }

    if (hasSolution) printf("x = %lld mod %lld\n", A, P);
    else printf("No solution\n");
    // A = 23, P = 210 => x = 23 mod 210
}
