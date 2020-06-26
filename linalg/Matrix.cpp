#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvl;
typedef pair<int,int> pii;
typedef long long ll;

vvl multiply(const vvl &A, const vvl&B, ll p){
    int n = A.size();
    int m = B[0].size();
    int c = A[0].size();
    vvl ans(n, vl(m,0));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<c;k++){
                ans[i][j] += (A[i][k] * B[k][j])%p;
                ans[i][j] %= p;
            }
        }
    }

    return ans;
}

vvl eye(int n){
    vvl ans(n,vl(n,0));
    for(int i=0;i<n;i++) ans[i][i] = 1;
    return ans;
}

void modPow(const vvl &A, ll n, ll p, vvl &ans){
    ans = eye(A.size());
    auto P2 = A;
    while(n){
        if(n&1){
            ans = multiply(ans, P2, p);
        }
        n >>= 1;
        P2 = multiply(P2, P2, p);
    }
}

class Matrix{
    public:
    vvl G;
    int n,m;
    static ll p;

    Matrix(int n = 1, int m = 1, int fill=0) :
        n(n) , m(m), G(n, vl(m,fill)) {
    }

    Matrix(const vvl& G) : n(G.size()), m(G[0].size()), G(G){
    }

    Matrix(const Matrix& o) : n(o.n), m(o.m), G(o.G){
    }

    Matrix& operator=(const Matrix& o){
        if(&o == this) return *this;        
        n = o.n;
        m = o.m;
        G = o.G;
        return *this;
    }
    
    static void set_mod(ll p){
        Matrix::p = p;
    }

    friend std::ostream& operator<< (std::ostream &s, const Matrix &M){
        for(int i=0;i<M.n;i++){
            s << "[";
            for(int j=0;j<M.m;j++){
                s << M.G[i][j] << (j<M.m-1 ? " ," : "");
            }
            s << "]" << endl;
        }
        return s;
    }
    
    Matrix operator*(const Matrix &B){
        assert(m == B.n);
        return Matrix(::multiply(G, B.G, p));
    }
	
    static Matrix eye(int n){
		return Matrix(::eye(n));
    }

    Matrix operator^(ll exp){
        Matrix ans(n,m);
        modPow(G, exp, p, ans.G);
        return ans;
    }

};
ll Matrix::p{1000000000}; //10^9

int main(){
    Matrix A(vvl{{0,1}, {1,1}});
    
    cout << (A^100000) << endl;
    
    return 0;
}