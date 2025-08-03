// longest increasing subsequence
vector<int> longestIncreasingSubsequence(vector<int>&v) {
	int n = (int)v.size();
	vector<int> len(n), seq, res;
	for (int i = 0; i < n; i++) {
		int idx = lower_bound(seq.begin(), seq.end(), v[i]) - seq.begin();
		if (idx == seq.size())
			seq.emplace_back(v[i]);
		else
			seq[idx] = v[i];
		len[i] = idx + 1;
	}

  // build
	int pos = max_element(len.begin(), len.end()) - len.begin();
	res.emplace_back(v[pos]);
	for (int i = pos - 1; i >= 0; i--) {
		if (len[pos] == len[i] + 1 && v[i] < v[pos]) {
			res.emplace_back(v[i]);
			pos = i;
		}
	}
	reverse(res.begin(), res.end());
	return res;
}



// longest non-decreasing subsequence
vector<int> longestNon_decreasingSubsequence(vector<int>&v) {
	int n = (int)v.size();
	vector<int> len(n), seq, res;
	for (int i = 0; i < n; i++) {
		int idx = upper_bound(seq.begin(), seq.end(), v[i]) - seq.begin();
		if (idx == seq.size())
			seq.emplace_back(v[i]);
		else
			seq[idx] = v[i];
		len[i] = idx;
	}

  // build
	int pos = max_element(len.begin(), len.end()) - len.begin();
	res.emplace_back(v[pos]);
	for (int i = pos - 1; i >= 0; i--) {
		if (len[pos] == len[i] + 1 && v[i] <= v[pos]) {
			res.emplace_back(v[i]);
			pos = i;
		}
	}
	reverse(res.begin(), res.end());
	return res;
}