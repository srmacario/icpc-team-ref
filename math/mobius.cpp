/**********************************************************************************
* MOBIUS FUNCTION (APPLY MOBIUS INVERSION)                                        *
* Description: The Mobius Function is defined as:                                 *
*              u(n) = 0,      if n has one or more repeated prime factors         *
*              u(n) = 1,      if n = 1                                            *
*              u(n) = (-1)^k, if n is a product of k distinct primes              *
* Needed to apply the Mobius inversion: "sum of u(d) for all d|n = (n == 1)", i.e.*
* 1 if n = 1, and 0 otherwise. Useful for gcd-related questions.                  *
* First values:   n    1   2   3   4   5   6   7   8   9  10  11  12              *
*               u(n)   1  -1  -1   0  -1   1  -1   0   0   1  -1   0              *
* Example: Calculate the number of coprime pairs between 1 and n, i.e.            *
*          #(x,y) : [gcd(x,y) = 1].                                               *
* Solution: sum i=1..n of sum j=1..n of (gcd(i,j) == 1)                           *
*           sum i=1..n of sum j=1..n of sum d|gcd(i,j) of u(d)                    *
*           sum i=1..n of sum j=1..n of sum d=1..n of [d|gcd(i,j)]*u(d)           *
*           sum i=1..n of sum j=1..n of sum d=1..n of [d|i]*[d|j]*u(d)            *
*           sum d=1..n of (sum i=1..n of [d|i])*(sum j=1..n of d|j)*u(d)          *
*           sum d=1..n of u(d)*(n/d)^2                                            *
* Useful tips and properties for gcd-related questions:                           *
* a) sum for all d|n of u(d) = sum for all d = 1..n [d|n]*u(d)                    *
* a) [d|gcd(i,j)] = [d|i][d|j]                                                    *
* b) sum for i = 1..n of [d|i] = (n/d)                                            *
* c) [gcd(ak,bk) = k] <=> [gcd(a,b) = 1]                                          *
* d) When sum for i = 1..n [d|i]*i, apply i = da                                  *
* e) When (n/kd), apply l = kd and loop for l first.                              *
* f) sum for all d|n of u(d)*n/d = phi(n)                                         *
**********************************************************************************/


// 1 if n == 1
// 0 if exists x | n%(x^2) == 0
// else (-1)^k, k = #(p) | p is prime and n%p == 0

//Calculate Mobius for all integers using sieve
//O(n*log(log(n)))
void mobius() {
  for(int i = 1; i < N; i++) mob[i] = 1;

  for(ll i = 2; i < N; i++) if(!sieve[i]){
    for(ll j = i; j < N; j += i) sieve[j] = i, mob[j] *= -1;
    for(ll j = i*i; j < N; j += i*i) mob[j] = 0;
  }
}

/*
//Calculate Mobius for 1 integer
//O(sqrt(n))
int mobius(int n){
  if(n == 1) return 1;
  int p = 0;
  for(int i = 2; i*i <= n; i++)
    if(n%i == 0){
      n /= i;
      p++;
      if(n%i == 0) return 0;
    }
  if(n > 1) p++;
  return p&1 ? -1 : 1;
}
*/
