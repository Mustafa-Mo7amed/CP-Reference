Bit Manipulation

__builtin_popcount() // count the number of 1's in an "int"

__builtin_popcountll() // count the number of 1's in an "long long"

__builtin_ctz() // count the number of trailing 0's (from the right to the left) in an "int"

__builtin_ctzll() // count the number of trailing 0's (from the right to the left) in an "long long"

__builtin_clz() // count the number of leading 0's (from the left to the right) in an "int"

__builtin_clzll() // count the number of leading 0's (from the left to the right) in an "long long"

__builtin_ffs(x) // returns 1 + the index of the least significant bit in x in an "int"

__builtin_ffsll(x) // returns 1 + the index of the least significant bit in x in an "long long"

Note: 
a + b = (a ^ b) + 2 * (a & b)
a + b = (a | b) + (a & b)

void print(ll num) {
	if (num <= 1) {
		cout << num;
		return;
	}
	print(num >> 1LL);
	cout << (num & 1LL);
}

bool getBit(ll num, int idx) {
	return ((num >> idx) & 1);
}

ll setBit(ll num, int idx, bool val) {
	return val ? (num | (1LL << idx)) : (num & ~(1LL << idx));
}

ll flipBit(ll num, int idx) {
	return (num ^ (1LL << idx));
}

ll leastBit(ll num) {
	return (num & -num);
}

//num%mod, mod is a power of 2
ll Mod(ll num, ll mod) {
	return (num & mod - 1);
}

bool isPowerOfTwo(ll num) {
	return (num & num - 1) == 0;
}

int turnOnLastZero(int S) {
	return S | S + 1;
}

int turnOffLastBit(int S) {
	return S & S - 1;
}

int turnOnLastConsecutiveZeroes(int S) {
	return S | S - 1;
}

int turnOffLastConsecutiveBits(int S) {
	return S & S + 1;
}