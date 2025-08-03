struct fastPrimeFactorization {
private:
	using u64 = uint64_t;
	using u128 = __uint128_t;
	vector<ll> factors;
	vector<ll> primeFactors;
	static ll mul_mod(ll a, ll b, ll mod) {
		return (__int128)a * b % mod;
	}
	u64 binPower(u64 base, u64 e, u64 mod) {
		u64 result = 1;
		base %= mod;
		while (e) {
			if (e & 1)
				result = (u128)result * base % mod;
			base = (u128)base * base % mod;
			e >>= 1;
		}
		return result;
	}
	u64 check_composite(u64 n, u64 a, u64 d, int s) {
		u64 x = binPower(a, d, n);
		if (x == 1 || x == n - 1)
			return false;
		for (int r = 1; r < s; r++) {
			x = (u128)x * x % n;
			if (x == n - 1)
				return false;
		}
		return true;
	}
	bool MillerRabin(uint64_t n) {
		if (n < 2)
			return false;
		int r = 0;
		u64 d = n - 1;
		while ((d & 1) == 0) {
			d >>= 1;
			r++;
		}
		for (int a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
			if (n == a)
				return true;
			if (check_composite(n, a, d, r))
				return false;
		}
		return true;
	}
	static ll rho(ll n) {
		ll d, c = rand() % n, x = rand() % n, xx = x;
		ll lim = 100000;
		if (n % 2 == 0)
			return 2;
		do {
			x = (mul_mod(x, x, n) + c) % n;
			xx = (mul_mod(xx, xx, n) + c) % n;
			xx = (mul_mod(xx, xx, n) + c) % n;
			d = __gcd(abs(x - xx), n);
		} while (d == 1 && lim--);
		return d;
	}
	// generate prime factors of n
	void factor(ll n) {
		if (n <= 1)
			return;
		stack<ll> st;
		st.emplace(n);
		while (!st.empty()) {
			n = st.top();
			st.pop();
			if (n == 1)
				continue;
			if (MillerRabin(n)) {
				primeFactors.emplace_back(n);
				continue;
			}
			ll d = rho(n);
			st.emplace(d);
			st.emplace(n / d);
		}
	}
	// generate all divisors using prime factors
	void findFactors(int i, ll cur, vector<pair<ll, int>>& PFs) {
		if (i == sz(PFs))
			return void(factors.emplace_back(cur));
		for (int j = 0; j <= PFs[i].second; j++) {
			findFactors(i + 1, cur, PFs);
			cur *= PFs[i].first;
		}
	}
public:
	fastPrimeFactorization() = default;
	// returns all prime factors of N sorted in a vector<ll>
	vector<ll> factorize(ll n) {
		factor(n);
		sort(primeFactors.begin(), primeFactors.end());
		return primeFactors;
	}
	// returns a vector<pair<ll, int>> where the first is the prime factor and the second is its frequency
	vector<pair<ll, int>> factorizePowersForm(ll n) {
		factor(n);
		map<ll, int> mp;
		for (auto& i : primeFactors)
			mp[i]++;
		vector<pair<ll, int>> ret;
		for (auto& [i, j] : mp)
			ret.emplace_back(i, j);
		return ret;
	}
	// returns all divisors of N sorted in a vector<ll>
	vector<ll> getFactors(ll n) {
		auto PFs = factorizePowersForm(n);
		findFactors(0, 1, PFs);
		sort(factors.begin(), factors.end());
		return factors;
	}
};