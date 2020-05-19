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
#define debug(...) cout << "[" << #__VA_ARGS__ << "]:", debugF(cout, __VA_ARGS__);
template<typename T> istream &operator>>(istream &is, vector<T> &v){ for (auto &x : v) is >> x; return is; }
template<typename T> ostream &operator<<(ostream &os, vector<T> &v){ for(int i = 0; i < v.size(); os << (i>0 ? " ":"") << v[i++]); os << "\n"; return os;}

ll expMod(ll a, ll b, ll mod){
    ll ans = 1;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return ans;
}

template<class T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

template<class T> T extGCD(T a, T b, T& x, T& y){
    // gcd is negative if min(a,b) < 0 and |min(a,b)| > |max(a,b)|
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    T x1, y1;
    T g = extGCD(b, a%b, x1, y1);
    // b * x1 + (a%b)*y1 = g
    // b * x1 + (a - (a/b)*b)*y1 = g
    // a*y1 + b*(x1 - (a/b)*y1) = g        
    x = y1;
    y = x1 - (a/b)*(y1);
    return g;
}

// https://cp-algorithms.com/
template<class T> bool diophatineEqSolver(T a, T b, T c, T &x0, T &y0, T &g) {
    //ax + by = c
    g = extGCD(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    // all solutions
    // x = x0 + k * b / g
    // y = y0 - k * a / g
    return true;
}

// https://cp-algorithms.com/
template<class T> bool modularEqSolver(T a, T b, T n, T& x){
    // ax = b (mod n)
    // ax + ny = b
    T x0, y0, g;
    if(!diophatineEqSolver(a,n,b, x0, y0, g)){
        return false;
    }
    x = (x0%n + n)%n;
    //x = (x0 + n)%n;
    // all solutions: x + i*(n/g) , for i in 0..g-1
    return true;
}

// https://cp-algorithms.com/
void modularInvRange(int n, int pMod, vi &inv){
    // all inverse mod p PRIME for i = 1 ... n
    n = min(n,pMod-1);
    inv = vi(n+1);
    inv[0] = 0; //undefined
    // inv[i] = -floor(p/i) * inv[p%i] , 1 <= i < p
    inv[1] = 1;
    for(int i=2;i<=n;i++){
        inv[i] = (-ll(pMod/i)*inv[pMod%i])%pMod;
        if(inv[i] < 0) inv[i] += pMod;
    }
}

// https://cp-algorithms.com/
int phiF(int n){
    // runtime O(sqrt(n))
    if(n <= 1) return n;
    int ans = n;
    for(int i = 2; i*i <= n; i++){
        if(n%i == 0){
            while(n%i == 0)
                n /= i;

            // ans = ans * (1 - 1/p)
            ans -= ans/i;
        }
    }
    if(n > 1)
        ans -= ans/n;
    return ans;
}

// https://cp-algorithms.com/
void phiRange(int n, vi& phi) {
    phi = vi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

class CRT{
    // Chinese Remainder Theorem
    public:
    vl p;
    vvl r;
    CRT(vl &pp) : p(pp) {
        int k = p.size();
        r = vvl(k);
        //r[j][i] = (p[i]^-1)%p[j], i < j
        for(int j=0;j<k;j++){
            for(int i=0;i<j;i++){
                ll x, y, g;
                g = extGCD(p[i], p[j], x, y);
                assert(g == 1);
                x %= p[j];
                if(x < 0)
                    x += p[j];
                r[j].push_back(x);
            }
        }
    }

    void garners(vl &a, vl &x){
        int k = a.size();
        x.resize(k);
        for (int i = 0; i < k; ++i){
            x[i] = a[i];
            for (int j = 0; j < i; ++j){
                x[i] = r[i][j] * (x[i] - x[j]);

                x[i] = x[i] % p[i];
                if (x[i] < 0)
                    x[i] += p[i];
            }
        }
    }

    ll compute(vl &x){
        //a = x1 + p1*x2 + p1*p2*x3 + ... p1*..*p_(k-1)*xk
        ll a = x[0];
        ll prod = p[0];
        for(int i=1;i<x.size();i++){
            a += prod*x[i];
            prod *= p[i];
        }
        return a;
    }
};

class DiscreteLog{
    /* BSGS
    a^x = b (mod) <=> a^(i + j*n) = b (mod)
    a^i = b*a^(-n * j) ,  0 <= i < n, 0 <= j <= mod/n
    */
    public:
    DiscreteLog(){ }

    static ll computeGeneral(ll a, ll b, ll mod){
        b %= mod;
        if(b == 1) return 0;
        ll aInv, y;
        ll g = extGCD(a, mod, aInv, y);
        if(g == 1){
            return computeCoprime(a, b, mod);
        }
        if(b%g != 0) return -1;
        //a ^ (x-1) = b* (a'^-1) (mod')
        mod /= g;
        aInv %= mod;
        if(aInv < 0) aInv += mod;
        b = (b/g)*aInv;
        ll res = computeGeneral(a, b, mod);
        if(res == -1) return -1;
        return res + 1;
    }

    static ll computeCoprime(ll a, ll b, ll mod){
        b %= mod;
        if(b == 1) return 0;
        ll n = ll(sqrt(mod));

        // baby steps
        ll anInv;
        unordered_map<ll,ll> pot;
        ll ai = 1;
        for(ll i=0;i<n;i++){
            if(i > 0 && ai == 1) break;
            pot[ai] = i;
            ai = (ai*a)%mod;
        }
        ll y, g, an = ai;
        g = extGCD(an, mod, anInv, y);
        assert(g == 1);
        anInv = (anInv%mod);
        if(anInv < 0) anInv += mod;

        // giant steps
        ll rs = b, nb = mod/n;
        for(ll j = 0; j <= nb; j++){
            if(pot.count(rs) > 0){
                ll i = pot[rs];
                return i + j*n;
            }
            rs = (rs*anInv)%mod;
        }
        return -1;
    }
};


// =============== TEST ===================
void testDiscreteLog(){
    int nt = 100;
    while(nt--){
        int mod = 1000 + rand()%(1000);
        int a = 1 + (rand()%(mod-1));
        vb has(mod, false);
        int ae = 1;
        for(int e = 0; e < mod; e++){
            has[ae] = true;
            auto res = DiscreteLog::computeGeneral(a, ae, mod);
            assert(res != -1);
            assert(expMod(a, res, mod) == ae%mod);
            ae = (ae*a)%mod;
        }
        for(int i=1;i<mod;i++){
            if(!has[i]){
                auto res = DiscreteLog::computeGeneral(a, i, mod);
                assert (res == -1);
            }
        }
    }
    cout << "discrete log ok" << endl;
}
void testCRT(){
    vl p = {6,5,7};
    int n = 1;
    for(auto &x : p) n *= x;
    CRT crt(p);
    for(int i=0;i<n;i++){
        vl a;
        for(auto &x : p)
            a.push_back(i%x);
        vl x;
        crt.garners(a, x);
        assert(crt.compute(x) == i); 
    }
    cout << "crt ok\n";
}

void testInvRange(){
    int p = 197;
    vi inv;

    modularInvRange(p, p, inv);
    for(int i = 1;i<p;i++){
        int inv2, _;
        extGCD(i,p,inv2, _);
        if(inv2 < 0) inv2 = (inv2%p + p)%p;
        assert(inv[i] == inv2);
    }
    cout << "test inv range ok" << endl;
}

void testGCD(){
    // 1276111009 1655801091    
    int p, q;
    int n = 10;
    srand(time(nullptr));
    while(n--){
        //cout << "Enter p and q " << endl;
        //cin >> p >> q;
        {
            int c = 1e9;
            p = -c + rand()%(2*c);
            q = -c + rand()%(2*c);
            cout << "p = " << p << " q = " << q << endl;
        }
        

        int x,y;
        int g = extGCD(p,q,x,y);
        assert(g == gcd(p,q));
        cout << p << " % " << q << " = " << p%q << endl;
        cout << p << " / " << q << " = " << p/q << endl;
        cout << p << " * " << x << " + " << q << " * " << y << " = " << g << endl;

        for(int i=0;i<10;i++){
            using num = ll;
            num qq = abs(q);
            num b = rand()%qq;
            // p*x = b (mod q)
            cout << p << "* x = " << b << " mod(" <<qq<< ")" << endl;
            num sol;
            if(!modularEqSolver(num(p), num(b), qq , sol)){
                cout << "no solution" << endl;
            }else
            {
                cout << "solution: " << sol << endl;
                auto pp = (num(p)%qq + qq)%qq;
                assert((pp*sol)%qq == b);
            }
        }

        cout << "gcd. modular eq. solver ok " << endl;
    }
}


void testPhi(){
    int n = 100;
    vi phi;
    phiRange(n, phi);
    for(int i = 1;i<=n;i++){
        assert(phi[i] = phiF(i));

        int cnt = 0;
        for(int j = 1;j<=i;j++)
            if(gcd(i,j) == 1) cnt++;
        assert(phi[i] == cnt);
    }
    cout << "phi ok" << endl;
}

int main(){
    
    testDiscreteLog();
    //testCRT();
    //testPhi();
    //testInvRange();
    //testGCD();
    
    return 0;
}