#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvl;
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

class WheelSieve{
    public:
    int b, s;
    vi baseL;
    vi r, inc, rI;
    vector<bool> isP;
    vector<bool> isBase;

    WheelSieve(const vi& firstPrimes): baseL{firstPrimes}{
        // baseL = first k primes
        sort(all(baseL));
        isBase.resize(baseL.back()+1, false);
        
        b = 1; int i;
        for(i=0;i<baseL.size();i++){
            b *= baseL[i];
            isBase[baseL[i]] = true;
        }
        
        for(i=1;i<b;i++){
            bool ok = true; //gcd(i, b) == 1;
            for(auto p : baseL){
                if(i%p == 0){
                    ok = false;
                    break;
                }
            }
            if(ok) r.push_back(i);
        }
        
        s = r.size();
        inc.resize(s);
        rI.resize(b,-1);
        for(i=0;i<s;i++){
            inc[i] = (r[(i+1)%s] - r[i] + b)%b;
            rI[r[i]] = i;
        }
    }

    int num(int i){
        return (i/s)*b + r[i%s];
    }

    int idx(int x){
        return (x/b)*s + rI[x%b];
    }

    void sieve(int n, vi &primeL){
        int i, size = (n/b)*s;
        for(i=0;i < s && r[i] <= (n%b);++i, ++size);
        if(isP.size() != size) isP.resize(size);
        fill(all(isP), true);
        isP[0] = false; //num(0) = 1
        primeL.clear(); primeL.reserve((n/32));
        for(auto p : baseL) primeL.push_back(p);

        ll p; int ib;
        vi incX(s);
        for(i = ib = 1, p = r[i];(i<size) && (p*p <= n); p += inc[ib], ++i, ib = (ib==s-1?0:ib+1)){
            if(!isP[i]) continue;
            //p is prime
            primeL.push_back(p);
            int j, currI, prevI = -1; ll pk, p2 = p*p;
            for(j = ib, pk = p2; pk <= n; pk += inc[j]*p, j = (j==s-1 ? 0:j+1)){
                currI = idx(pk);
                isP[currI] = false;
                if(prevI != -1) incX[(j-1==-1?s-1:j-1)] = currI - prevI;
                prevI = currI;
                if(j == ib && (pk > p2)) break;
            }
            if(pk <= n){
                currI += incX[j];
                j = (j==s-1 ? 0:j+1);
                for(; currI < size; currI += incX[j], j = (j==s-1 ? 0:j+1)){
                    isP[currI] = false;
                }
            }
        }
        // tail primes > sqrt(n) : only needed for primeL
        for(;i<size;p += inc[ib], ++i, ib = (ib==s-1?0:ib+1)){
            if(isP[i]) primeL.push_back(p);
        }
    }

    bool isPrime(int x){
        if(x <= baseL.back()) return isBase[x];
        if(rI[x%b] < 0) return false;
        return isP[idx(x)];
    }
};

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

void testSieve(){
    int n = 100000000;
    
    auto begin = std::chrono::steady_clock::now();
    WheelSieve W({2,3,5,7,11});
    vi primeL;
    W.sieve(n, primeL);
    //cout << primeL.size() << endl;
    auto end = std::chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

    begin = std::chrono::steady_clock::now();
    vi primeL2; 
    vector<bool> isP;
    sieve(n, primeL2,isP);
    //vi minP;
    //linearSieve(n, minP, primeL2);
    end = std::chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

    assert(primeL.size() == primeL2.size());

    for(int i=0;i<primeL.size();i++){
        assert(primeL[i] == primeL2[i]);
    }

    for(int i=0;i<=n;i++){
        assert(isP[i] == W.isPrime(i));
    }
    
    cout << "ok" << endl;
}

int main(){
    testSieve();
}