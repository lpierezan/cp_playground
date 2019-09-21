#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

class SparseTable{
public:
    vvi dp; //dp[i][j] = max(v[i] .. v[i + 2^j -1])
    SparseTable(vi& v){
        int n = v.size();
        int k = log2(n) + 2;
        dp = vvi(n, vi(k, 0));
        int i,j,r;
        
        for(i=0;i<n;i++) dp[i][0] = v[i];
        
        for(j=1;j<k;j++){
            for(i=0;i<n;i++){
                dp[i][j] = dp[i][j-1];
                r = i + (1<<(j-1));
                if(r < n)
                    dp[i][j] = max(dp[i][j], dp[r][j-1]);
            } 
        }
    }

    int query(int i, int j){
        if(j < i) swap(i,j);
        int k = 0;
        while((i + (1<<k) - 1) <= j){
            k++;
        }
        k--; // i + (1<<k) - 1) <= j
        int r = j - ((1<<k)-1);
        int ans = max(dp[i][k],dp[r][k]);
        return ans;
    }
    int size(){
        return dp.size();
    }
    int at(int i){
        return dp[i][0];
    }
};
