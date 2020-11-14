/**********************************************************************************
* PRIMITIVE ROOT (NUMBER WHICH CAN GENERATE ALL MULTIPLICATIVE GROUP MOD P)       *
* Description:  a number g is called a primitive root modulo p if every number    *
* coprime to p is congruent to a power of g modulo p. Mathematically, g is a      *
* primitive root modulo p if and only if for any integer a such that gcd(a,p)=1,  *
* there exists an integer k such that:  g^k = a(mod p). k is then called the index*
* or discrete logarithm of a to the base g modulo p. g is also called the         *
* generator of the multiplicative group of integers modulo p. In particular,      *
* for the case where p is a prime, the powers of primitive root runs through all  *
* numbers from 1 to p−1.                                                          *
* Time complexity: O(log^6(p))                                                    *
**********************************************************************************/

// Finds a primitive root modulo p
// To make it works for any value of p, we must add calculation of phi(p)
// n is 1, 2, 4 or p^k or 2*p^k (p odd in both cases)
ll root(ll p) {
  ll n = p-1;
  vector<ll> fact;

  for (int i=2; i*i<=n; ++i) if (n % i == 0) {
    fact.push_back (i);
    while (n % i == 0) n /= i;
  }

  if (n > 1) fact.push_back (n);

  for (int res=2; res<=p; ++res) {
    bool ok = true;
    for (size_t i=0; i<fact.size() && ok; ++i)
      ok &= exp(res, (p-1) / fact[i], p) != 1;
    if (ok)  return res;
  }

  return -1;
}
