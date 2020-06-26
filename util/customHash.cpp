#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define all(x) (x).begin(), (x).end()
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
void debugF(ostream &os) {os << endl;}
template <typename Head, typename... Tail>
void debugF(ostream &os, Head H, Tail... T) { os << " " << H; debugF(os, T...); }
#define debug(...) cout << "[" << #__VA_ARGS__ << "]:", debugF(cout, __VA_ARGS__)
template<typename T> istream &operator>>(istream &is, vector<T> &v){ for (auto &x : v) is >> x; return is; }
template<typename T> ostream &operator<<(ostream &os, vector<T> &v){ for(int i = 0; i < v.size(); os << (i>0 ? " ":"") << v[i++]); return os;}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<long long, int, custom_hash> safe_map;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int a, b;
        cin >> a >> b;
        safe_map[a] = b;
    }

    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << safe_map[x] << "\n";
    }
    
    return 0;
}

