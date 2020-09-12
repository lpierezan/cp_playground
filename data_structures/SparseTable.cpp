#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

struct SparseTable{
    vvi dp; //dp[i][j] = max(v[i] .. v[i + 2^j -1])
    vi logF; //logF[x] = max j | 2 ^ j <= x

    SparseTable(vi& v){
        int n = v.size();
        int i, j, k = 0;
        //2^k > n
        while((1<<k) <= n) k++;
        dp = vvi(n, vi(k, 0));
        
        logF.resize(n+1);
        logF[1] = 0;
        for(i=2;i<=n;i++){
            logF[i] = logF[i/2] + 1;
        }

        for(i=0;i<n;i++){
            dp[i][0] = v[i];
        }
        for(j=1;j<k;j++){
            for(i=0; i + (1<<j) <= n;i++){
                int jmp = (1<<(j-1));
                dp[i][j] = max(dp[i][j-1], dp[i+jmp][j-1]);
            }
        }
    }

    int query(int l, int r){
        int sz = r - l + 1;
        int j = logF[sz];
        int q1 = dp[l][j];
        int q2 = dp[r - (1<<j) + 1][j];
        return max(q1,q2);
    }
};

int main(){
    vi v = {5,3,1,4,5,10,6,2,4,5};
    SparseTable S(v);
    cout << S.query(0,3)<< endl;
    cout << S.query(0,5)<< endl;
    cout << S.query(1,1)<< endl;
}
