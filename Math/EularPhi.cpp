// Euler's Totient for counting how many numbers less than N where GCD(N, i) == 1 (co-prime)
ll EulerPhi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0)
            res -= res / i;
        while (n % i == 0)
            n /= i;
    }
    if (n != 1)
        res -= res / n;
    return res;
}

// computing euler's phi totient for all i where 0 <= i <= n
vector<ll> generateEulerPhi(ll n) {
    vector<ll> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}