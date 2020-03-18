#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

static int gcd(int a, int b){
    int tmp;
    if(b == 0)
        return a;
        
    while(a%b != 0){
        tmp = a;
        a = b;
        b = tmp%b;
    }
    return b;
}

static int extGCD(int a, int b, int& x, int& y){
    // gcd is negative if min(a,b) < 0 and |min(a,b)| > |max(a,b)|
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extGCD(b, a%b, x1, y1);
    // b * x1 + (a%b)*y1 = g
    // b * x1 + (a - (a/b)*b)*y1 = g
    // a*y1 + b*(x1 - (a/b)*y1) = g        
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {    
    g = extGCD(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    // x = x0 + k * b / g
    // y = y0 - k * a / g
    return true;
}


int main(){
    
    int p, q;
    int n = 100;
    while(n--){
        cout << "Enter p and q " << endl;
        cin >> p >> q;

        int x,y;
        int g = extGCD(p,q,x,y);
        cout << p << " % " << q << " = " << p%q << endl;
        cout << p << " / " << q << " = " << p/q << endl;
        cout << p << " * " << x << " + " << q << " * " << y << " = " << g << endl;
        cout << endl;
    }
    
    return 0;
}