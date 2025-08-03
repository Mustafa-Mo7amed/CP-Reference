ll sum(ll n) { return (n / (long double)2) * (n + 1); }

// same without using long double
ll sum(ll n) {
    if (n & 1) {
        return n * ((n + 1) / 2);
    } else {
        return (n / 2) * (n + 1);
    }
}


// sum of numbers that are divisible by x from x to n

ll sum(ll n, ll x) {
    n -= n % x;
    return ((n / x) / (long double) 2) * (n + x);
}

// same without using long double
ll sum(int n, int x) {
    // sum of multiples of x up to n: x * (k(k+1)/2), where k = n/x
    ll k = n / x;
    if (k & 1) {
        return x * (k * ((k + 1) / 2));
    } else {
        return x * ((k / 2) * (k + 1));
    }
}

// sum of numbers that are divisible by x range from l to r

ll sumRange(ll l, ll r, ll x) {
	l--;
	l -= l % x, r -= r % x;
	return sum(r, x) - sum(l, x);
}

//return sum of sequence a, a+x , a+2x .... b
ll sumSequence(ll a, ll b, ll x) {
	a = ((a + x - 1) / x) * x;
	b = (b / x) * x;
	return (b + a) * (b - a + x) / (2 * x);
}

// reverse_sum

long double rev_sum(ll n) { return (-1 + sqrtl(1 + 8 * n)) / 2; }

// geometric sum

// a is the first term, n is the number of terms, r is the ratio

// 2 + 4 + 8 + 16 + 32 >> n = 5, r = 2

// 3 + 9 + 27 + 81 + 243 >> n = 5, r = 3

ll geoSum(ll a, ll n, ll r) {
  // returns a*(r^n - 1)/(r - 1), for r!=1
  return a * (fastPow(r,n) - 1) / (r - 1);
}
