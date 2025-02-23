// first parameter is a vector<int> axis which holds the indices to be compressed
// second parameter is a vector<int> in which every index points to the original value in vector<int> axis
// third parameter is a map<int, int> its key is the original value of vector<int> axis and its value is the compressed index assigned to this "original value"
// the values in vector<int> axis will change to the compressed indices
// vector<int> indexToValue: indexToValue[pos] = originalValue, "pos" is the compressed index of "originalValue"
// map<int, int> valueToIndex: valueToIndex[originalValue] = pos, "originalValue" is the original value in axis and "pos" is its compressed index
void coordinate_compression(vector<int>& axis, vector<int>& indexToValue, map<int, int>& valueToIndex, int start = 1, int step = 1) {
	for (auto& x_pos : axis)
		valueToIndex[x_pos] = 0;
	indexToValue.resize(start + step * (int)valueToIndex.size());
	int idx = 0;
	for (auto& [value, index] : valueToIndex) {
		index = start + step * idx;
		indexToValue[index] = value;
		++idx;
	}
	for (auto& x_pos : axis)
		x_pos = valueToIndex[x_pos];
}



// takes a vector by value and sort it then assign every unique value in it to an index [0: n - 1]
struct coordinateCompression {
	vector<ll> init;
	explicit coordinateCompression(const vector<ll>& v) {
		init = v;
		sort(init.begin(), init.end());
		init.erase(unique(init.begin(), init.end()), init.end());
	}
	// returns the compressed index of the given value
	int index(ll val) {
		return lower_bound(init.begin(), init.end(), val) - init.begin();
	}
	// returns the initial value of the compressed index (idx)
	ll initVal(int idx) {
		return init[idx];
	}
};