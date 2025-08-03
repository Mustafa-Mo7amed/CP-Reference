const int N = 2e6 + 20, mod = 1e9 + 7;
int fact[N], modInv[N];
int fp(int n, int p) {
	if (!p)
		return 1;
	int res = fp(n, p >> 1) % mod;
	res *= res;
	res %= mod;
	return p & 1LL ? res * (n % mod) % mod : res;
}
int mod_inv(int a) { return fp(a, mod - 2); }
void pre() {
	fact[0] = fact[1] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % mod;
		modInv[i] = mod_inv(fact[i]);
	}
}
int nCr(int n, int r) { return fact[n] * mod_inv(fact[r] * fact[n - r] % mod) % mod; }