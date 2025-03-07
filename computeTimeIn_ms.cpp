#include <bits/stdc++.h>
#include <chrono>
using namespace std;
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    // code
    int cnt = 0;
    for (size_t i = 0; i < 1e9; i++) {
        cnt++;
    }
    cout << "cnt = " << cnt << '\n';
    // end
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Elapsed time (ms): " << duration_ms << std::endl;
    return 0;
}
