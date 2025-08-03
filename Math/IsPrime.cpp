// returns true if n is prime, else returns false. Time Complexity -> O(sqrt(n) / 6)
bool isPrime(ll x) {
	if (x == 2 || x == 3)
		return true;
	if (x <= 1 || x % 2 == 0 || x % 3 == 0)
		return false;
	for (int i = 5; (ll)i * i <= x; i += 6)
		if (x % i == 0 || x % (i + 2) == 0)
			return false;
	return true;
}
