vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while(s[i - p[i]] == s[i + p[i]]) {
            ++p[i];
        }
        if(i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher_even(const string& s) {
    int n = s.size();
    string t;
    t.reserve(2*n+1);
    for (char c : s) {
        t.push_back('#');
        t.push_back(c);
    }
    t.push_back('#');

    auto d = manacher_odd(t);

    vector<int> p(n);
    for (int i = 0; i < n; i++)
        p[i] = d[2*i] / 2;
    return p;
}