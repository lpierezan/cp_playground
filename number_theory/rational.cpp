#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

class rational{
public:

    static int mdc(int a, int b){
        int tmp;
        while(a%b != 0){
            tmp = a;
            a = b;
            b = tmp%b;
        }
        return b;
    }

    static vi continued_fraction(int p, int q){
        // p/q = continued fraction: [a0; a1, a2, ... , 1]
        vi ans;
        int a,p_;
        do{
            a = p/q;
            ans.push_back(a);
            p_ = p%q;
            // p/q = a + p_/q ---> ans = [a] + continued_fraction(q/p_)
            p = q;
            q = p_;
        }while(q != 0);
        if(*ans.rbegin() != 1){
            (*ans.rbegin()) -= 1;
            ans.push_back(1);
        }
        return ans;
    }

    // https://en.wikipedia.org/wiki/Continued_fraction
    static vector<pii> convergents(vi cont_frac_seq){
        // seq must be in [a0;.., 1] format for the second-last convergent appears
        int h[2] = {0,1};
        int k[2] = {1,0};

        int a, h_curr, k_curr;
        vector<pii> ans;

        for(int i=0; i < (int)cont_frac_seq.size();i++){
            a = cont_frac_seq[i];
            h_curr = a*h[1] + h[0];
            k_curr = a*k[1] + k[0];
            cout << h_curr << " / " << k_curr << " = " << double(h_curr)/k_curr << endl;
            ans.push_back(mp(h_curr,k_curr));
            h[0] = h[1], h[1] = h_curr;
            k[0] = k[1], k[1] = k_curr;
        }
        return ans;
    }
};

int main(){
    
    int p, q;
    int n = 100;
    while(n--){
        cout << "Enter p and q " << endl;
        cin >> p >> q;
        vi ans = rational::continued_fraction(p, q);
        cout << p << "/" << q << " = " << double(p)/q << endl;
        cout << "continued fraction: ";
        for(auto x : ans){
            cout << x << " ";
        }
        cout << endl;
        cout << "convergents: " << endl;
        rational::convergents(ans);
        cout << endl;
    }
    
    return 0;
}