// Time Complexity -> O(n loglog(n))
// sets prime indices in vector "isPrime" to "true" if the index is prime, else "false"
// stores all primes in vector "primes"
vector<int> primes; // stores all primes from 2 -> n
vector<bool> isPrime; // memory can be optimized here by using a bitset, but is slightly slower in accessing the elements
void sieve(int n) {
	isPrime.assign(n + 1, true);
	primes.assign(1, 2);
	isPrime[0] = isPrime[1] = false;
	for (int i = 4; i <= n; i += 2)
		isPrime[i] = false;
	for (int i = 3; (ll)i * i <= n; i += 2) {
		if (!isPrime[i])
			continue;
		// primes.emplace_back(i); will work without the loop underneath, but we'll need to change the outer loop condition to "i <= n"
		for (int j = i * i; j <= n; j += i + i)
			isPrime[j] = false;
	}
	// storing all primes from 2 -> n
	for (int i = 3; i <= n; i++)
		if (isPrime[i])
			primes.emplace_back(i);
}