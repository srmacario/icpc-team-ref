/**********************************************************************************
* FACTORIZING (GET PRIME FACTORS OF A NUMBER + THEIR EXPONENTS)                   *
* Description: Factorates a number into its prime factors.                        *
* Example: 150 = (2^1)*(3^1)*(5^2) => if f = factorize(150) then f[2] = 1,        *
* f[3] = 1, f[5] = 2.                                                             *
* Time complexity: O(sqrt(N)/log(sqrt(N)))                                        *
* Usage: f = factorize(x), f[i] returns exponent of factor i                      *
**********************************************************************************/

// + PRIMES LIST

map<int, int> factorize(int n) {
    map<int, int> fact;
    for(int i = 0; pr[i]*pr[i] <= n; i++)
        while (n % pr[i] == 0) fact[pr[i]]++, n /= pr[i];
    if (n > 1) fact[n]++;
    return fact;
}

map <int, int> f;

int main () {
    primes();
    f = factorize(150);
    return 0;
}

/**********************************************************************************
* NUMBER OF DIVISORS (HOW MANY X <= N MEET N % X == 0?)                           *
* Description: Derivated from the Factorizing algorithm, it counts how many       *
* divisors a number has.                                                          *
* Example: divisors(4) = 3 because 4%4=0, 4%2=0 and 4%1=0.                        *
* Time complexity: O(sqrt(N)/log(N))                                              *
* Usage: divisors(x)                                                              *
* Notation: ret:     return value                                                 *
*           expon:   exponent value of a prime factor in the factorization of n   *
**********************************************************************************/

// + PRIMES LIST

ll divisors (int n) {
    ll ret = 1, expon = 1;
    for(int i = 0; pr[i]*pr[i] <= n; ++i) {
        while (n % pr[i] == 0) expon++, n /= pr[i];
        ret *= expon, expon = 1;
    }
    if (n > 1) ret *= 2;
    return ret;
