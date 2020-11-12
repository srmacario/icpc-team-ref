/**********************************************************************************
* Z-FUNCTION (STRING MATCHING AND MORE)                                           *
* Description: z[i] = longest common prefix between s and its substring s[i..n-1] *
* Time complexity: O(N)                                                           *
* Notation: Z:   vector with the z function of q = p + '$' + s                    *
*           s:   main string                                                      *
*           p:   substring to be found                                            *
* Example:  For s = "baabaa" and p = "aab", q = "aab$baabaa" and each z[i] = 3    *
*           indicates a match.                                                    *
* Note:     A sub-matching is when the substring differs by 1 character from the  *
*           pattern: "abc" and "abd" are a sub-match. To achieve this, we also    *
*           need to calculate the z("rev(p) + '$' + rev(s)").                     *
**********************************************************************************/

string s, p, q;

vi Z (string q) {
    vi z(q.size());
    for (int i = 1, l = 0, r = 0, n = q.size(); i < n; i++) {
        if (i <= r) z[i] = min(z[i-l], r-i+1);
        while (i + z[i] < n and q[z[i]] == q[z[i] + i]) z[i]++;
        if (i+z[i]-1 > r) {
            l = i;
            r = i+z[i]-1;
        }
    }
    return z;
}

int main () {

    /* String matching - O(N+M) */
    string s, p, q;
    cin >> s >> p;
    q = p + '$' + s;

    vi v = Z(q);
    for (int i = p.size(); i < q.size(); i++)
        if (v[i] == p.size()) {
            // matching position i-p.size()-1 (+1?)
        }

    /* String sub-matching (at most 1 character
       different from the pattern) - O(N+M) */

    string s, p, q;
    cin >> s >> p;

    string rs = s; reverse(rs.begin(), rs.end());
    string rp = p; reverse(rp.begin(), rp.end());
    string q1 =  p + '#' + s;
    string q2 = rp + '#' + rs;
    vi z1 = Z(q1);
    vi z2 = Z(q2);

    for (int i = p.size(); i < q1.size(); i++) {
        if (z1[i] + z2[q1.size()-i+1] >= p.size()-1) {
            // matching position i-p.size()-1 (+1)?
        }
    }

    /* String compression: Find the smallest
       cyclic unit of a string - O(N), e.g.
       "abcabcabc" => "abc",
       "aaaaaaaaa" => "a",
       "icpc"      => "icpc"
       (see UVa 455 - Periodic Strings)       */

    string s;
    cin >> s;

    string ans = {s[0]};
    int n = s.size();
    vi z = Z(s);
    for (int i = 1; i < n; i++) {
        if (n % i == 0 and i + z[i] == n) break;
        ans += s[i];
    }
    cout << ans << endl;

    /* Extend to Palindrome: Add the fewest number of
       letters such that s becomes a palindrome. - O(N)
       (see UVa 1175 - Extend to Palindrome)            */

    string s;
    cin >> s;

    string t = s;
    reverse(t.begin(), t.end());
    string q = t + '$' + s;
    vi z = Z(q);

    int ans = 0;
    for (int i = n; i < z.size(); i++) {
        if (i + z[i] == z.size()) {
            ans = z[i];
            break;
        }
    }

    if (ans) {
        int ind = s.size()-ans-1;
        for (int i = ind; i >= 0; i--) s += s[i];
    }
    cout << s << endl;

    /* Number of distinct substrings - O(N^2) */
    /* Iterative approach: starting with an empty string and adding letter
       by letter, calculate many new substrings are formed each time.      */

    string s;
    cin >> s;

    string t = "";
    int ans = 0;
    for (auto c : s) {
        t += c;
        vi v = z(t);
        int zmax = 0;
        for (auto x : v) zmax = max(zmax, x);
        ans += t.size()-zmax;
    }
    cout << ans << endl;

}

