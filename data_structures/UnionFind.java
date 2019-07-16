public class UnionFind{
    /*
    par[v] = -(# of elements in v´s set), if v is root
    par[v] = j >= 0, if j is parent of v    
    -1 represents empty set
    */

    int[] par;

    UnionFind(int n){
        par = new int[n];
        for(int i=0;i<n;i++) par[i] = -1;
    }
    
    int root(int v){
        if(v == -1) return v;
        return par[v] < 0 ? v : (par[v] = root(par[v]));
    }

    void merge(int u, int v){
        u = root(u);
        v = root(v);
        if(u == -1 || v == -1 || (u == v)) return;
    
        if(par[u] >= par[v]){
            int tmp = u;
            u = v;
            v = tmp;
        }
        //link v -> u
        par[u] += par[v];
        par[v] = u;
    }

    int size(int u){
        if(u == -1) return 0;
        return - par[root(u)];
    }
}