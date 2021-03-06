#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

class BipartiteGraph{
    /* 
        Bipartide graph with n vertices on the left and m vertices on the right.
        Index with [0,n-1] on the left and [n,n+m-1] on the right.
    */
   
public:

    vector<vector<int>> g;
    int n, m;

    BipartiteGraph(int n, int m) : n(n), m(m), g(n+m,vi()){
    }

    void add_edge(int v, int u){
        if(u < v) swap(u,v);
        assert(v >= 0 && v < n && u >= n && u < n+m);
        g[v].push_back(u);
        g[u].push_back(v);
    }

    void remove_edge(int v, int u){
        if(u < v) swap(u,v);
        assert(v >= 0 && v < n && u >= n && u < n+m);
        int i = 2;
        while(i--){
            auto pos = find(all(g[v]), u);
            if(pos != g[v].end()) g[v].erase(pos);
            swap(u,v);
        }
    }

    bool augment(int v, vector<bool> &used, vector<int> &match){
        used[v] = true;
        for (int u : g[v]){
            if (used[u]) continue;
            used[u] = true;
            bool found_path = false;
            if (match[u] < 0){
                found_path = true;
            }else if(!used[match[u]]){
                int vv = match[u];
                if(augment(vv, used, match)){
                    found_path = true;
                }
            }
            if(found_path){
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching(vi &match, const vector<pii> &freeze){
        vector<bool> used(n + m);
        match.resize(n+m);
        fill(all(match), -1);
        int ans = 0;
        for(auto x : freeze){
            match[x.first] = x.second;
            ans++;
        }
        for (int i = 0; i < n; i++)
        {
            fill(all(used), false);
            for(auto x : freeze){
                used[x.first] = true;
                used[x.second] = true;
            }
            if(used[i]) continue;
            if (augment(i, used, match))
                ans++;
            if(ans == min(n,m))
                break;
        }
        return ans;
    }

    int max_matching(){
        vi _; vector<pii> __;
        return max_matching(_, __);
    }

    string to_string(){
        stringstream s;
        s << "n = " << n << " m = " << m << endl;
        for(int i=0;i<n;i++){
            s << "N(" << i << ") = ";
            for(auto u : g[i])
                s << u << " ";
            s << endl;
        }
        return s.str();
    }
};

int main()
{
    // https://www.hackerrank.com/challenges/real-estate-broker/problem
    int n, m;

    cin >> n >> m;

    vector<pii> client(n);
    vector<pii> house(m);

    int i,j,x,y;

    for(i=0;i<n;i++){
        cin >> x >> y;
        client[i] = mp(x,y);
    }
    for(i=0;i<m;i++){
        cin >> x >> y;
        house[i] = mp(x,y);
    }
    
    
    BipartiteGraph g(n,m);

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(client[i].first < house[j].first && client[i].second >= house[j].second){
                g.add_edge(i, j+n);
            }
        }
    }

    //cout << g.to_string() << endl;

    cout << g.max_matching() << endl;

    return 0;
}