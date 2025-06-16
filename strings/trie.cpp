// if the alphabet is small consider using array<int, 26> instead of map
// modify haveNext and [] operator accordingly don't forget (ch - 'a') or whatever
// if the number of nodes is known in advance you may pass it to the constructor to reserve it (more optimal)
class trie {
    struct node {
        bool isLeaf{};
        map<char, int> next;
        bool haveNext(const char ch) const {
            return next.find(ch) != next.end();
        }
        int& operator[](const char ch) {
            return next[ch];
        }
    };
    vector<node> t;
public:
    trie(const int reserveNodes = 0) {
        t.reserve(reserveNodes);
        t.emplace_back();
    }
    void insert(const string& s) {
        int root = 0;
        for (const char ch : s) {
            if (!t[root].haveNext(ch)) {
                t.emplace_back();
                t[root][ch] = t.size() - 1;
            }
            root = t[root][ch];
        }
        t[root].isLeaf = true;
    }
    bool find(const string& s) {
        int root = 0;
        for (const char ch : s) {
            if (!t[root].haveNext(ch))
                return  false;
            root = t[root][ch];
        }
        return t[root].isLeaf;
    }
    bool findPrefix(const string& s) {
        int root = 0;
        for (const char ch : s) {
            if (!t[root].haveNext(ch))
                return  false;
            root = t[root][ch];
        }
        return true;
    }
};