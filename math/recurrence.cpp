/**********************************************************************************
* RECURRENCE FORMULA                                                              *
* Description: Enables fast calculation of the f(n) in a recurrence.              *
* Example: Calculate 100000th term of Fibonacci sequence                          *
* Time complexity: O(k^3 log(n))                                                  *
* Usage: f(n)                                                                     *
**********************************************************************************/

// for f(n) = a(1)*f(n-1) + a(2)*f(n-2) + ... + a(k)*f(n-k), then:

// A = | a(1)     1   0   0  ...  0  |
//     | a(2)     0   1   0  ...  0  |
//     | a(3)     0   0   1  ...  0  |
//     | ...     ... ... ... ... ... |
//     | a(k-1)   0   0   0  ...  1  |
//     | a(k)     0   0   0  ...  0  |

//     | f(n+k-1) f(n+k-2) f(n+k-3) ... f(n) | =

//   = |  f(k-1)   f(k-2)   f(k-3)  ... f(0) | A^n

// Example: f(n) = 4*f(n-1) - f(n-2)

// A = | 4  1 |
//     | -1 0 |

//     | f(n+1) f(n) | =

//   = | f(1)   f(0) | A^n

const int MOD = 1e9+7;

vector <vector <ll> > A, AN, B, C, D;

void mul () {
    // Resizing and clearing D
    D.resize(B.size());
    for (auto& row : D) row.resize(C[0].size());
    for (auto& row : D)
        for (auto& elem : row)
            elem = 0;

    // Multiplying B*C = D
    for (int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D[i].size(); j++) {
            for (int k = 0; k < B[0].size(); k++) {
                D[i][j] += B[i][k]*C[k][j];
                D[i][j] %= MOD;
            }
        }
    }
}

// Fast matrix exponential to get A^n
void getAN (ll n) {
    AN.clear();
    AN.resize(A.size());
    for (auto& row : AN) row.resize(A[0].size());

    for (int i = 0; i < AN.size(); i++)
        AN[i][i] = 1;

    ll e = n;
    while (e) {
        if (e&1) {
            B = AN;
            C = A;
            mul();
            AN = D;
        }
        B = A;
        C = A;
        mul();
        A = D;
        e >>= 1;
    }
}

ll f (ll n) {
    if (n < 0) return 0;

    // ATTENTION: Fill k and A, with the coeff
    ll k = 4; // number of coeff in the recurr
    A.resize(k);
    A[0] = {16,1, 0, 0};
    A[1] = {9, 0, 1, 0};
    A[2] = {4, 0, 0, 1};
    A[3] = {1, 0, 0, 0};

    getAN(n);
    C = AN;

    B.resize(1);
    // ATTENTION: Fill with matrix B =
    // = | f(k)  f(k-1)  f(k-2) ... f(1) |,
    // the first values for f
    B[0] = {4388, 265, 16, 1};

    mul();
    return D[0].back();
}
