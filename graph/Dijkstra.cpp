#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

class Dijkstra{
public:
    static vi solve(vector<vector<pii>> &g, int s, int target = -1){
        //g[v] = list of (u,w) , where v->u with weight w.
        int n = g.size();
        assert(s >= 0 && s < n);

        vi dist(n, -1);
        vector<bool> used(n, false);
        set<pii> S;
        S.insert(mp(0, s));
        
        while(!S.empty()){
            auto min_data = *S.begin();
            S.erase(S.begin());

            int min_dist = min_data.first;
            int v = min_data.second;
            dist[v] = min_dist;
            used[v] = true;

            if(target == v)
                break;

            for(auto u_data : g[v]){
                int u = u_data.first;
                int w = u_data.second;
                if(w < 0){
                    throw new invalid_argument("graph with negative edges");
                }
                if(used[u])
                    continue;                    
                if(dist[u] == -1 || (dist[v]+w < dist[u])){
                    if(dist[u] != -1)
                        S.erase(mp(dist[u],u));
                    dist[u] = dist[v] + w;
                    S.insert(mp(dist[u],u));
                }
            }
        }
        return dist;
    }
};

int main(){
    // https://www.spoj.com/problems/HIGHWAYS/

    int nt, it;
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> nt;
    for(it=1;it<=nt;it++){
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        s--;t--;
        
        // build graph bidirectional from edges
        vector<vector<pii>> g(n);
        for(int i=0;i<m;i++){
            int v,u,w;
            cin >> v >> u >> w;
            v--;u--;
            g[v].push_back(mp(u,w));
            g[u].push_back(mp(v,w));
        }

        vi dist;
        dist = Dijkstra::solve(g, s, t);
        if(dist[t] < 0){
            cout << "NONE" << endl;
        }else{
            cout << dist[t] << endl;
        }
    }
    return 0;
}