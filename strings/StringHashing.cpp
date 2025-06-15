// generates a random number in the range [l, r]
// randomize the base for string hashing (make sure to use the same base for all strings in the same context)
static mt19937 rng(static_cast<uint32_t>(chrono::steady_clock::now().time_since_epoch().count()));
long long rand(long long l, long long r) {
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}

// regular string hashing
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



// permutation string hashing (where the order of characters doesn't matter)
struct StringPermutationHash {
    const int mod = 1e9 + 9;
    int n{};
    ll base{};
    vector<ll> power, pre;
    StringPermutationHash() = default;
    StringPermutationHash(const string& s, ll b): n(s.size()), base(b) {
        power.reserve(n);
        pre.reserve(n);
        ll p = 1;
        for (int i = 0; i < 26; ++i) {
            power.emplace_back(p);
            p *= base;
            p %= mod;
        }
        for (int i = 0; i < n; ++i) {
            if (pre.empty())
                pre.emplace_back(s[i] * power[s[i] - 'a'] % mod);
            else
                pre.emplace_back((pre.back() + s[i] * power[s[i] - 'a']) % mod);
        }
    }
    ll get(int l, int r) {
        if (l == 0)
            return pre[r];
        return (pre[r] - pre[l - 1] + mod) % mod;
    }
};


// 128-bit string hashing (to avoid collisions)
// when you use M hash codes in a string of length N, the probability of a collision is at most (M^2 * N) / mod
// hence using a larger mod is a must
struct StringHash {
    const ll mod = (1LL << 61) - 1;
    int n{};
    ll base{};
    vector<__int128> power, pre;
    StringHash() = default;
    StringHash(const string& s, ll b): n(s.size()), base(b) {
        power.reserve(n);
        pre.reserve(n);
        __int128 p = 1;
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
    __int128 get(int l, int r) {
        if (l == 0)
            return pre[r] * power[n - 1] % mod;
        return (pre[r] - pre[l - 1] + mod) % mod * power[n - l - 1] % mod;
    }
};