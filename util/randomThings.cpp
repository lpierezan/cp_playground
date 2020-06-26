#include <bits/stdc++.h>

using namespace std;

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

int main(){
    int n = 10;
    while(n--){
        cout << rng() << "\n";
    }
    return 0;
}
