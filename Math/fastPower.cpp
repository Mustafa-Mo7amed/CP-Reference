ll fpow(ll n, ll p) {
	if (!p)
		return 1;
	ll res = fpow(n, p >> 1LL);
	res *= res;
	return p & 1 ? res * n : res;
}

ll fpow(ll n, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1LL)
			res *= n;
		n *= n;
		p >>= 1;
	}
	return res;
}


ll powMod(ll n, ll p, ll m) {
	if (!p)
		return 1;
	ll res = powMod(n, p >> 1, m) % m;
	res *= res;
	res %= m;
	return p & 1LL ? (res * (n % m)) % m : res;
}

ll mod_inv(ll a, ll m) { return powMod(a, m - 2, m); }

// sum of pow(5, 1) + pow(5, 2) + ... + pow(5, p)
// O(log(p) * log(p))
ll sumPow(ll n, ll p, ll mod) {
	if (p == 1)
		return n % mod;
	ll res = sumPow(n, p >> 1, mod) % mod;
	res += (res * powMod(n, p >> 1, mod)) % mod;
	if (p & 1LL)
		res += powMod(n, p, mod);
	return res % mod;
}