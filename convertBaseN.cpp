t == 1 >> convert from any base to decimal
t == 2 >> convert from decimal to any base

#include <bits/stdc++.h>
#define see(x) cout << (#x) << " = " << x << '\n'
#define ll long long
using namespace std;
map<char, ll> mp;
map<ll, char> mp2;

void Generate() {
	for (char i = '0'; i <= '9'; i++) {
		mp[i] = i - '0';
	}
	for (char i = 'A'; i <= 'Z'; i++) {
		mp[i] = i - 'A' + 10;
	}
	for (ll i = 0;i <= 9;i++) {
		mp2[i] = (char)(i + '0');
	}
	for (int i = 10;i <= 35;i++) {
		mp2[i] = (char)(i - 10 + 'A');
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	Generate();
	ll t;
	cin >> t;
	if (t == 1) {
		ll x;
		string s;
		cin >> s >> x;
		reverse(s.begin(), s.end());
		ll sum = 0;
		for (int i = 0; i < s.size(); i++) {
			sum += (ll)powl(x, i) * mp[s[i]];
		}
		cout << sum;
	}
	else {
		string res;
		ll n, x;
		cin >> n >> x;
		ll remainder;
		while (n) {
			remainder = n % x;
			n /= x;
			res += mp2[remainder];
		}
		reverse(res.begin(), res.end());
		cout << res;
	}
	return 0;
}