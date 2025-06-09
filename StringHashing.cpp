struct StringHash {
    const int mod = 1e9 + 9;
    int n{}, base{};
    vector<ll> power, pre;
    StringHash() = default;
    StringHash(const string& s, int b): n(s.size()), base(b) {
        power.reserve(n);
        pre.reserve(n);
        ll p = 1;
        for (int i = 0; i < n; ++i) {
            power.emplace_back(p);
            if (pre.empty())
                pre.emplace_back(s[i] * p % mod);
            else
                pre.emplace_back((pre.back() + s[i] * p) % mod);
            p *= base;
            p %= mod;
        }
    }
    ll get(int l, int r) {
        if (l == 0)
            return pre[r] * power[n - 1] % mod;
        return (pre[r] - pre[l - 1] + mod) % mod * power[n - l - 1] % mod;
    }
};