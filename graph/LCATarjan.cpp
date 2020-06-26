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

class UnionFind{
  public:
  vector<int> par;
  UnionFind(int n) : par(n,-1) {}

  int root(int v){
    if(v == -1) return v;
    return par[v] < 0 ? v : (par[v] = root(par[v]));
  }

  void merge(int u, int v){
    u = root(u); v = root(v);
    if(u == -1 || v == -1 || (u == v)) return;
    if(par[u] >= par[v]) swap(u,v);
    //link v -> u
    par[u] += par[v];
    par[v] = u;
  }

  int size(int u){
    return u == -1 ? 0 : -par[root(u)];
  }
};

vvi g;
vector<vector<pii>> qr;
UnionFind U(1);
vi anc;
vb clr;

void dfsLCA(int v){
    clr[v] = true;
    anc[v] = v;
    for(auto u : g[v]){
        if(!clr[u]){
            dfsLCA(u);
            U.merge(v,u);
            anc[U.root(v)] = v;
        }
    }
    for(auto ui : qr[v]){
        int u,iq;
        tie(u,iq) = ui;
        if(clr[u]){
            cout << "LCA(" << v << "," << u << ") = " << anc[U.root(u)] << "\n";
        }
    }
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q, i, u, v;
    cin >> n >> q;
    g.clear();g.resize(n);
    for(i=0;i<n-1;i++){
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    qr.clear(); qr.resize(n);
    for(i=0;i<q;i++){
        cin >> u >> v;
        u--;v--;
        qr[u].push_back({v,i});
        qr[v].push_back({u,i});
    }

    U = UnionFind(n);
    clr.assign(n, false);
    anc.resize(n);
    dfsLCA(0);
    
    return 0;
}