#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

vector<pair<long,int>> fac(ll n){
    vector<pair<long,int>> ret;
    if(n <= 1){
        return ret;
    }
    int j = 1;
    for(ll p = 2; p*p <= n; p += j){
        int exp = 0;
        while(n%p == 0){
            n /= p;
            exp++;
        }
        if(exp != 0)
            ret.push_back(mp(p, exp));
        if(p > 2) j = 2;
    }
    if(n > 1){
        ret.push_back(mp(n,1));
    }
    return ret;
}

ll expMod(ll a, ll exp, ll mod){
    if(exp == 0) return 1;
    ll pa = expMod(a, exp/2, mod);
    pa = (pa*pa)%mod;
    if(exp%2 == 1) pa = (pa*a)%mod;
    return pa;
}

int main(){
    ll n;
    cin >> n;
    auto facs = fac(n);
    for(auto pe : facs){
        cout << pe.first << "^" << pe.second << " ";
    }

}