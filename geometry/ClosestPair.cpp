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

// https://cp-algorithms.com/geometry/nearest_points.html

struct Point{
    int x,y,idx;
};

bool cmp_x(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}
bool cmp_y(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

ll minDist2 = 1e18;
int mnI, mxI;
void updateMin(const Point &p1, const Point &p2){
    ll x = p1.x - p2.x;
    ll y = p1.y - p2.y;
    ll d2 = x*x + y*y;
    if(d2 < minDist2){
        minDist2 = d2;
        mnI = min(p1.idx, p2.idx);
        mxI = max(p1.idx, p2.idx);
    }
}

void closetPair(vector<Point> &P, int l, int r){
    int i, j;
    if(r-l+1 <= 3){
        for(i=l;i<=r;i++){
            for(j=i+1;j<=r;j++){
                updateMin(P[i], P[j]);
            }
        }
        sort(P.begin() + l, P.begin() + r + 1, cmp_y);
        return;
    }
    int md = l + (r-l)/2;
    int mdx = P[md].x;
    closetPair(P, l, md);
    closetPair(P, md+1, r);
    inplace_merge(P.begin()+l, P.begin()+md+1, P.begin()+r+1, cmp_y);
    
    deque<int> Q;
    for(i=l;i<=r;i++){
        ll x = P[i].x - mdx;
        if(x*x >= minDist2) continue;
        while(!Q.empty()){
            ll y = P[i].y - P[Q.front()].y;
            if(y*y < minDist2) break;
            else{
                Q.pop_front();
            }
        }
        assert(Q.size() < 8);
        for(auto idx : Q){
            updateMin(P[i], P[idx]);
        }
        Q.push_back(i);
    }
}

// https://www.spoj.com/problems/CLOPPAIR/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<Point> P(n);
    for(int i=0;i<n;i++){
        cin >> P[i].x;
        cin >> P[i].y;
        P[i].idx = i;
    }    
    minDist2 = 1e18;
    sort(all(P), cmp_x);
    closetPair(P, 0, n-1);
    double minDist = sqrt(minDist2);
    cout << mnI << " " << mxI << " " << fixed << setprecision(6) << minDist << "\n";
    return 0;
}