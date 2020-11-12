
/**********************************************************************************
* KNUTH OPTIMIZATION ( dp[i][k] = min j<k {dp[j][k-1] + C(j,i)} )                 *
* Description: uses the monotocity condition (bounded above and below) to find    *
* optimal point.                                                                  *
* Condition: L[i][k-1] <= L[i][k] <= L[i+1][k]                                    * 
* Time Complexity: O(K*N^2) becomes O(K*N)                                        *                
* Notation: dp[i][k]: optimal solution using k positions, until position i        *
*           L[i][k]: optimal point, smallest j which minimizes dp[i][k]           *
*           C(i,j): cost for splitting range [j,i] to j and i                     *
**********************************************************************************/

const int N = 1e3+5;

ll dp[N][N], L[N][N];

//Cost for using i and j
ll C(ll i, ll j);

//Initialize DP
for(ll i=1;i<=n;i++){
    //dp[i,1] = cost from 0 to i
    L[n+1][i] = n;
}

for(ll l = 2; l<=k; l++){
    for(ll i=n; i>=1; i--){
        //best: cost, pos
        pair<ll,ll> best = {LINF, n};
        //searches best using the necessary condition
        for(ll j = L[i][l-1]; j <= L[i+1][l] and j < i; j++){
            best = min(best, {dp[j][l-1] + C(j, i), j});
        }
        dp[i][l] = best.first;
        L[i][l] = best.second;
    }
}

//+ Iterate over i to get min{dp[i][k]}, don't forget cost from n to i
