// adds two numbers
string add(const string& s, const string& t) {
	vector<ll> d(sz(s)), N(sz(t));
	for (int i = 0; i < sz(s); i++)
		d[i] = s[i] - '0';
	for (int i = 0; i < sz(t); i++)
		N[i] = t[i] - '0';
	if (sz(N) < sz(d)) {
		int dif = sz(d) - sz(N);
		reverse(N.begin(), N.end());
		while (dif--)
			N.emplace_back(0);
		reverse(N.begin(), N.end());
	}
	else if (sz(N) > sz(d)) {
		int dif = sz(N) - sz(d);
		reverse(d.begin(), d.end());
		while (dif--)
			d.emplace_back(0);
		reverse(d.begin(), d.end());
	}
	for (int i = 0; i < sz(d); ++i)
		d[i] += N[i];
	ll carry = 0;
	for (int i = sz(d) - 1; i >= 0; --i) {
		ll sum = d[i] + carry;
		d[i] = sum % 10;
		carry = sum / 10;
	}
	string res;
	if (carry)
		res += to_string(carry);
	for (const ll& i : d)
		res += to_string(i);
	return res;
}

// multiplies two numbers
string multiply(const string& s, const string& t) {
	vector<ll> d(sz(s)), N(sz(t));
	for (int i = 0; i < sz(s); i++)
		d[i] = s[i] - '0';
	for (int i = 0; i < sz(t); i++)
		N[i] = t[i] - '0';
	int _ = sz(N);
	while (_--) {
		reverse(d.begin(), d.end());
		d.emplace_back(0);
		reverse(d.begin(), d.end());
	}
	_ = sz(N) - 1;
	while (_--)
		d.emplace_back(0);
	vector<ll> res;
	for (int i = sz(d) - 1; i > sz(N) - 1; i--) {
		ll sum = 0;
		int k = i;
		for (const ll j : N)
			sum += j * d[k--];
		res.emplace_back(sum);
	}
	reverse(res.begin(), res.end());
	ll carry = 0;
	for (int i = sz(res) - 1; i >= 0; --i) {
		ll sum = res[i] + carry;
		res[i] = sum % 10;
		carry = sum / 10;
	}
	string ans;
	if (carry)
		ans += to_string(carry);
	for (const ll& i : res)
		ans += to_string(i);
	return ans;
}

// returns the factorial of a number
string bigFactorial(const string& n) {
	string f = "0", res = "1";
	while (true) {
		f = add(f, "1");
		res = multiply(res, f);
		if (f >= n) {
			if (f.size() >= n.size())
				break;
		}
	}
	return res;
}

// returns the number % mod
unsigned ll bigMod(const string& s, ll mod) {
	unsigned ll res = 0;
	for (auto& i : s) {
		res *= 10;
		res += i - '0';
		res %= mod;
	}
	return res;
}