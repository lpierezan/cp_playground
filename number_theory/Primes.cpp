#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

ll expMod(ll a, ll exp, ll mod){
    if(exp == 0) return 1;
    ll pa = expMod(a, exp/2, mod);
    pa = (pa*pa)%mod;
    if(exp%2 == 1) pa = (pa*a)%mod;
    return pa;
}

void sieve(int n, vi &primeList, vector<bool> &isP){
    // O(n) (bool) memory
    // O(nloglogn) runtime

    primeList.clear();
    isP.clear();
    isP.resize(n+1, true);
    isP[0] = isP[1] = false;
    ll i;
    for(i = 2; i * i <= n;i++){
        if(isP[i]){
            primeList.push_back(i);
            for(ll j = i*i; j <= n; j += i){
                isP[j] = false;
            }
        }
    }
    for(;i<=n;i++){
        if(isP[i]){
            primeList.push_back(i);
        }
    }   
}

void blockSieve(ll l, ll r, const vi &primeList, vector<bool> &isP){
    // O(r-l+1) mem
    // primeList[-1]**2 >= r
    // l >= 0
    int block = r - l + 1;
    
    if(isP.size() != block){
        isP.resize(block);
    }
    fill(all(isP), true);

    if(l<=0) isP[0] = false;
    if(l<=1&&r>=1) isP[1-l] = false;

    for(ll p : primeList){
        if(p*p > r) break;
        ll k = (l+p-1)/p; //ceil(l/p)
        k = max(k, p); // k >= p => k*p >= p**2
        int idx = k*p - l;
        for(;idx < block;idx+=p){
            isP[idx] = false;
        }
    }
}

void linearSieve(int n, vi &minP, vi &primeList){
    // minP[i] = minimum prime in i factorization
    // minP[0] = minP[1] = -1
    // O(n) (int) mem
    // O(n) runtime

    minP.clear(); minP.resize(n+1,0);
    primeList.clear();

    minP[0] = minP[1] = -1;
    for(int i=2;i<=n;++i){
        if(minP[i] == 0){
            minP[i] = i;
            primeList.push_back(i);
        }
        ll x;
        for(int j=0;j < primeList.size() && primeList[j] <= minP[i];++j){
            x = ll(i) * primeList[j];
            if(x > n) break;
            minP[x] = primeList[j];
        }
    }
}

vector<pair<ll,int>> fac(ll n, const vi &primeList){
    // primeList should cover sqrt(n)
    // O(pi(sqrt(n))) ~ O(sqrt(n)/log(sqrt(n)))

    vector<pair<ll,int>> ret;
    if(n <= 1){
        return ret;
    }
    ll p;
    int exp;
    for(int i = 0;i < primeList.size();++i){
        p = primeList[i];
        if(p*p > n) break;
        exp = 0;
        while(n%p == 0){
            n /= p;
            ++exp;
        }
        if(exp){
            ret.push_back({p,exp});
        }
    }
    if(n > 1){
        ret.push_back({n,1});
    }
    return ret;
}

vector<pair<long,int>> fac(ll n){
    // O(sqrt(n))
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

int main(){
    
    while(true){
        ll l,r;
        cin >> l >> r;
        int n = sqrt(r) + 1;
        vi primeList; vector<bool> isP;
        sieve(n, primeList, isP);
        
        cout << "fist 10 primes:" << endl;
        for(int i=0;i<10 && i < primeList.size();i++) cout << primeList[i] << " ";
        cout << endl;

        cout << "in the interval" << endl;
        vector<bool> isPB;
        blockSieve(l,r,primeList,isPB);
        int cnt = 0;
        for(int i=l;i<=r;i++){
            if(isPB[i-l]){
                cnt++;
                cout << i << " ";
            }
            if(cnt == 10) break;
        }
        cout << endl;
    }
}