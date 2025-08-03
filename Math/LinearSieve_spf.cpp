// Linear Sieve and Smallest Prime Factor
// finds all primes from 2 -> n
// Time Complexity -> O(n)
vector<int> spf; // stores the smallest prime factor of index (i), Note: spf[i] == i if i is a prime number
vector<int> primes; // stores all primes from 2 -> n
void linear_sieve(int n) {
    primes.reserve(n / log(n) * 1.1);
    spf.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.emplace_back(i);
        }
        for (auto& p : primes) {
            if (p > n / i)
                break;
            spf[i * p] = p;
            if (spf[i] == p)
                break;
        }
    }
}
bool isPrime(int x) {
    assert(x < spf.size());
    return spf[x] == x && x >= 2;
}