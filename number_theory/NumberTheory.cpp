#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

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


// =============== TEST ===================
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
    
    testPhi();
    //testInvRange();
    //testGCD();
    
    return 0;
}