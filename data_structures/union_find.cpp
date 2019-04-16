#include <vector>
#include <iostream>

using namespace std;

class UnionFind{
  /*
  par[v] = -(# of elements in v´s set), if v is root
  par[v] = j >= 0, if j is parent of v    
  -1 represents empty set
  */

  vector<int> par;
  public:
    UnionFind(int n){
      par.clear();
      par.resize(n, -1);
    }
    
    int root(int v){
      if(v == -1) return v;
      return par[v] < 0 ? v : (par[v] = root(par[v]));
    }

    void merge(int u, int v){
      u = root(u);
      v = root(v);
      if(u == -1 || v == -1 || (u == v)) return;

      if(par[u] >= par[v])
        swap(u,v);
      
      //link v -> u
      par[u] += par[v];
      par[v] = u;
    }

    int size(int u){
      if(u == -1) return 0;
      return - par[root(u)];
    }

};


int main(){
  UnionFind d = UnionFind(10);
  d.merge(1,2);
  d.merge(2,3);
  cout << d.root(1) << " " << d.root(2) << " " << d.root(3) << " " << d.root(4);
  
  cout << " " << endl;

  return 0;
}