#include <bits/stdc++.h>
using namespace std;

//multiv
template<class... Args> auto create(size_t n, Args&&... args) { if constexpr(sizeof...(args) == 1) return vector(n, args...); else return vector(n, create(args...));}

int main(){
    auto x = create(10,10,false);
    for(int i=0;i<5;i++)
        x[i][i].flip();
    cout << x[4][4] << endl;
    return 0;
}