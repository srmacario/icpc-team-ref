
/**********************************************************************************
* HASHING                                                                         *
* Time complexity: O(N) to precompute                                             *
* Notation: s:   main string                                                      *
*           hash:   hash from 1 to n                                              *
*           invhash: hash from n to 1                                             *
*           n:   s length                                                         *
*           m:   length of palindrome substring you are searching                 *
**********************************************************************************/


//++ fexp

int main(){
    int n,m;
    string s;
    cin >> n >> m >> s;
    vector <ll> hash (n+5), invhash(n+5), p(n+5), invp(n+5);
    hash[0] = invhash[0] = 0;
    invp[0] = invp[1] = p[0] = p[1] = 1;
    for(int i=1;i<=n;i++){
        if(i != 1){
            //ṕrecompute p^i and inv(p^1)
            p[i] = (p[i-1] * B) % MOD;
            invp[i] = fexp(p[i],MOD - 2, MOD);
        }
        //calculate hash as a prefix sum
        hash[i] = (hash[i-1] + ((s[i-1] - 'a' + 1) * p[i])%MOD)  % MOD;
    }
    for(int i=n;i>=1;i--){
        //calculate hash from inverse string
        invhash[n-i+1] = (invhash[n - i] + ((s[i-1] - 'a' + 1) * p[n-i+1])%MOD) % MOD;
    }
    for(int i=1;i<=n-m+1;i++){
        //index [l1,r1] from normal string and [l2,r2] from reverse string, if both are equal its palindrome
        //pay attention to odd m
        ll l1 = i, r1 = i + m/2 - 1, r2 = n - r1 - m%2, l2 = r2 - m/2 + 1;
        //using the prefix sum already calculated, we can find hash[l1,r1] and hash[l2,r2]
        ll h1 = (((hash[r1] - hash[l1 - 1] + MOD) % MOD) * invp[l1]) % MOD;
        ll h2 = (((invhash[r2] - invhash[l2 - 1] + MOD) % MOD) * invp[l2]) % MOD;
        if(h1 == h2){
            cout << "Accept\n";
            return 0;
        }
    }
    cout << "Reject\n";
    return 0;
}
