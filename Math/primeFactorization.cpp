// get all prime factors of a number
// Time Complexity -> O(sqrt(n))
vector<ll> getPrimeFactors(ll n) {
    vector<ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n != 1) {
        factors.push_back(n);
    }
    return factors;
}

// get all prime factors of a number pair<prime, count>
// Time Complexity -> O(sqrt(n))
vector<pair<ll, int>> primeFact(ll n) {
    if (n < isprime.size() && isprime[n])
        return {{n, 1}};
	vector<pair<ll, int>> v;
	for (auto& i : primes) {
		if ((ll)i * i > n || (n < (int)isprime.size() && isprime[n]))
			break;
		int cnt = 0;
		while (!(n % i)) {
			cnt++;
			n /= i;
		}
		if (cnt)
			v.emplace_back(i, cnt);
	}
	if (n > 1)
		v.emplace_back(n, 1);
	return v;
}