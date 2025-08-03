// IsPrime using Miller Rabin algorithm

// returns true if n is prime, else returns false. Time Complexity -> O(12 * log(n) * log(n))
bool isPrime(uint64_t n) {
    using ull = uint64_t;

    // Multiply (a * b) % mod safely without overflow
    auto mulmod = [](ull a, ull b, ull mod) -> ull {
        ull result = 0;
        a %= mod;
        while (b) {
            if (b & 1)
                result = (result + a) % mod;
            a = (a << 1) % mod;
            b >>= 1;
        }
        return result;
    };

    // Fast exponentiation using mulmod
    function<ull(ull, ull, ull)> binPower = [&](ull base, ull e, ull mod) {
        ull result = 1;
        base %= mod;
        while (e) {
            if (e & 1)
                result = mulmod(result, base, mod);
            base = mulmod(base, base, mod);
            e >>= 1;
        }
        return result;
    };

    function<bool(ull, ull, ull, ull)> check_composite = [&](ull n, ull a, ull d, int s) {
        ull x = binPower(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1)
                return false;
        }
        return true;
    };

    if (n < 2)
        return false;

    int r = 0;
    ull d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}