ll gcd(ll a, ll b) {
	while (b) {
		ll x = a;
		a = b;
		b = x % b;
	}
	return a;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Extended Euclidean algorithm

ll extended_gcd(ll a, ll b, ll& x, ll& y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll g = extended_gcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

// Mod Inverse

// works for any a, m, even if m is not prime
ll mod_inv(ll a, ll m) {
	ll x, y;
	extended_gcd(a, m, x, y);
	return (x % m + m) % m;
}

// only if m is prime
ll mod_inv(ll a, ll m) { return powMod(a, m - 2, m); }


// LCM
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }