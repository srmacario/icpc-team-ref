/**********************************************************************************
* PRIMES LIST (SIEVE OF ERATOSTHENES)                                             *
* Description: Generates an array with every prime from 2 to N.                   *
* Time complexity: O(N*log(log(N)))                                               *
* Usage: p[i]                                                                     *
**********************************************************************************/

const int N = 1e6+10; // Upper limit to n

int cmp[N];
vi pr;

void primes() {
    for (ll i = 2; i < N; i++) if (!cmp[i]) {
        for (ll j = i*i; j < N; j += i) cmp[j] = 1;
        pr.pb(i);
    }
}
