// number of divisors using prime factorization
// use sieve to generate all primes for better time complexity
// multiplication rule
ll numberOfDivisors(ll n) {
	ll res = 1;
	for (ll i = 2; i * i <= n; i++) {
		int cnt = 0;
		while (n % i == 0) {
			cnt++;
			n /= i;
		}
		res *= cnt + 1;
	}
	if (n != 1)
		res *= 2;
	return res;
}

// summation of divisors using prime factorization
// use sieve to generate all primes for better time complexity
// geometric series
ll sumOfDivisors(ll n) {
    ll res = 1;
    for (ll i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            cnt++;
            n /= i;
        }
        ll x = fpow(i, cnt + 1) - 1;
        res *= x / (i - 1);
    }
    if (n != 1) {
        ll x = fpow(n, 2) - 1;
        res *= x / (n - 1);
    }
    return res;
}