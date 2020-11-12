
/**********************************************************************************
* SUFFIX ARRAY (PATTERN FINDING, LONGEST COMMON SUBSTRING)                        *
* Description: A suffix array is an array of all suffixes of string,              *
*              lexicographically sorted.                                          *
* Example: Let the given string be "abacaba".                                     *
*                                                                                 *
*        0 abacaba                          6 a                                   *
*        1 bacaba     sort the suffixes     4 aba                                 *
*        2 acaba      ---------------->     0 abacaba                             *
*        3 caba        alphabetically       2 acaba                               *
*        4 aba                              5 ba                                  *
*        5 ba                               1 bacaba                              *
*        6 a                                3 caba                                *
*                                                                                 *
* So the suffix array for "abacaba" is {6, 4, 0, 2, 5, 1, 3}.                     *
* If a pattern t appears in s, it is a prefix of some suffix of s. Since the      *
* suffix array is lexicographically sorted, we can just make a binary search for  *
* each letter of the pattern.                                                     *
* Time complexity: O(NlogN)                                                       *
* Notation: sa:  suffix array vector, where sa[i] indicates a suffix beginning at *
*                s[sa[i]]                                                         *
**********************************************************************************/

// s.pb('$') (not necessary for pattern finding)

typedef vector <int> vi;
typedef pair <int, int> pii;

vi suffix_array(string &s){
    int n = s.size(), alph = 256;
    vector<int> cnt(max(n, alph)), p(n), c(n);

    for (auto c : s) cnt[c]++;
    for (int i = 1; i < alph; i++) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    for (int i = 1; i < n; i++)
        c[p[i]] = c[p[i-1]] + (s[p[i]] != s[p[i-1]]);

    vi c2(n), p2(n);

    for (int k = 0; (1 << k) < n; k++){
        int classes = c[p[n-1]] + 1;
        fill(cnt.begin(), cnt.begin() + classes, 0);

        for (int i = 0; i < n; i++) p2[i] = (p[i] - (1 << k) + n)%n;
        for (int i = 0; i < n; i++) cnt[c[i]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[p2[i]]]] = p2[i];

        c2[p[0]] = 0;
        for (int i = 1; i < n; i++){
            pii b1 = {c[p[i]], c[(p[i] + (1 << k))%n]};
            pii b2 = {c[p[i-1]], c[(p[i-1] + (1 << k))%n]};
            c2[p[i]] = c2[p[i-1]] + (b1 != b2);
        }

        c.swap(c2);
    }
    return p;
}

// s = text
// sa = suffix array of text s
// t = pattern to be found
// match(s, sa, t) = check if t if a substring of s
bool match (string& s, vi& sa, string& t) {
    int l = 0, m, r = sa.size()-1;

    while (l < r) {
        m = (l+r)/2;

        int res = strncmp(t.c_str(), s.c_str()+sa[m], t.size());
        if (res == 0) return true;
        if (res < 0) r = m-1;
        else         l = m+1;
    }

    int res = strncmp(t.c_str(), s.c_str()+sa[l], t.size());
    return (res == 0);
}

// sa = suffix_array(s);
// Example: s = "icpc", t = "cp" => match(s, sa, t) = true
//          s = "icpc", t = "ci" => match(s, sa, t) = false

// Longest Common Prefix with SA O(n)
vi lcp (string &s, vi &p) {
    int n = s.size();
    vi ans(n-1), pi(n);
    for (int i = 0; i < n; i++) pi[p[i]] = i;

    int lst = 0;
    for (int i = 0; i < n-1; i++){
        if (pi[i] == n-1) continue;
        while (s[i+lst] == s[p[pi[i]+1] + lst]) lst++;

        ans[pi[i]] = lst;
        lst = max(0, lst-1);
    }

    return ans;
}

// Longest Repeated Substring - O(n)
int lrs = 0;
for (int i = 0; i < n; i++) lrs = max(lrs, lcp[i]);

// Longest Common Substring - O(n)
// m = s.size();
// s = s + "$" + p + "#";
// n = s.size();
// vi sa = suffix_array(s)
int lcs = 0;
for (int i = 1; i < n; i++)
    if ((sa[i] < m) != (sa[i-1] < m))
        lcs = max(lcs, lcp[i]);

// To calculate LCS for multiple texts use a sliding window with minqueue
// The number of different substrings of a string is n*(n + 1)/2 - sum(lcs[i])
