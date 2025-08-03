// get all divisors of a number
// Time Complexity -> O(sqrt(n))
vector<ll> getDivisors(ll n) {
    vector<ll> divisors;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.emplace_back(i);
            if (i * i != n) {
                divisors.emplace_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}