#include <bits/stdc++.h>

using namespace std;
#define all(x) (x).begin(), (x).end()
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvl;
typedef pair<int,int> pii;
typedef long long ll;
void debugF(ostream &os) {os << endl;}
template <typename Head, typename... Tail>
void debugF(ostream &os, Head H, Tail... T) { os << " " << H; debugF(os, T...); }
#define debug(...) cout << "[" << #__VA_ARGS__ << "]:", debugF(cout, __VA_ARGS__)
template<typename T> istream &operator>>(istream &is, vector<T> &v){ for (auto &x : v) is >> x; return is; }
template<typename T> ostream &operator<<(ostream &os, vector<T> &v){ for(int i = 0; i < v.size(); os << (i>0 ? " ":"") << v[i++]); return os;}

struct BIT{
    vi bit;
    int n;

    BIT(int n) : n(n) , bit(n+1, 0) {
    }

    void add(int i, int val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }
    
    int sum(int i) {
        int ret = 0;
        for (; i >= 1; i -= i & -i)
            ret += bit[i];
        return ret;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nt;
    cin >> nt;
    for(int tt=1;tt<=nt;tt++){
    }
    return 0;
}