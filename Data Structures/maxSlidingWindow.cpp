// Sliding window maximum/minimum
// returns a vector ret where. ret[i] = max_element from i to i + k - 1; k is the fixed size of the subarray
// this one calculates the maximum if the minimum is needed instead just flip the comparison operators in the while loops
// O(n)
vector<int> maxSlidingWindow(vector<int>& nums, int k) { // careful the data type is INT
    deque<int> d;
    vector<int> ret;
    for (int i = 0; i < k; i++) {
        while (!d.empty() && nums[i] > nums[d.back()])
            d.pop_back();
        d.push_back(i);
    }
    for (int i = k; i < nums.size(); i++) {
        ret.push_back(nums[d.front()]);
        if (!d.empty() && d.front() <= i - k)
            d.pop_front();
        while (!d.empty() && nums[i] >= nums[d.back()])
            d.pop_back();
        d.push_back(i);
    }
    ret.push_back(nums[d.front()]);
    return ret;
}