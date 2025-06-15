// pi[i] = the length of the longest proper prefix of the substring s[0..i] which is also a suffix of this substring.
vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}
// KMP cheat sheet:
// keyword: substring, prefix, suffix, string equalities, pattern matching, string search
// typically processing for the pattern similar to input S
// try to find solution in: S, SS, rev(S), S@S, and so on