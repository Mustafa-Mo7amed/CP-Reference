// best version (less collisions)
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        size_t hash1 = hash<T1>{}(p.first);
        size_t hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

// same as above, but with more collisions
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        size_t hash1 = hash<T1>{}(p.first);
        size_t hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};



// (a, b) == (b, a)
struct hash_pair {
      template <class T1, class T2>
      size_t operator()(const pair<T1, T2>& p) const
      {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            
            if (hash1 != hash2) {
                  return hash1 ^ hash2;
            }
            
            return hash1;
      }
};