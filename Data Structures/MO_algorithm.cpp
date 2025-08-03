const int SQRT_N = 175;  // sqrt(n), change for different time complexity
struct query {
	int l, r, q_idx, block_idx;
	query() = default;
	query(int _l, int _r, int _q_idx) {
		l = _l - 1, r = _r - 1, q_idx = _q_idx, block_idx = _l / SQRT_N;
	}
	bool operator<(const query& y) const {
		if (block_idx != y.block_idx)
			return block_idx < y.block_idx;
		return r < y.r;
	}
};
struct MO {
	int n, q; // input array size, query size
	ll result; // final result
	vector<ll> input, query_answer;
	vector<query> queries;

	// You need to update following data structure
	// per problem (e.g. use mutliset)
	vector<int> freq;

	MO(const vector<ll>& input, const vector<query>& queries) : input(input), queries(queries) {
		n = (int)input.size();
		q = (int)queries.size();
		result = 0;
		query_answer.assign(q, 0);
		freq.assign(1000005, 0);
	}

	// You need to update these 2 methods per a problem
	void add(int idx) {
		freq[input[idx]]++;
		if (freq[input[idx]] == 1)
			result++;
	}
	void remove(int idx) {
		freq[input[idx]]--;
		if (freq[input[idx]] == 0)
			result--;
	}

	void process() {  // don't change
		sort(queries.begin(), queries.end());
		int curL = 1, curR = 0; // tricky initialization and indexing
		for (int i = 0; i < q; i++) {
			while (curL < queries[i].l) remove(curL++);
			while (curL > queries[i].l) add(--curL);
			while (curR < queries[i].r) add(++curR);
			while (curR > queries[i].r) remove(curR--);
			query_answer[queries[i].q_idx] = result;
		}
	}
};