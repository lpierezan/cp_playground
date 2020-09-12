#include <bits/stdc++.h>

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

struct SegTree{
    /*
        Range Min Queries
        - root at vertex 1
    */

    struct Data
    {
        int val;
        Data(int x) : val(x) {};
        Data() : Data(0) {};

        static Data combine(Data *ln, Data *rn){
            if(ln == nullptr) return *rn;
            if(rn == nullptr) return *ln;
            auto val = min(ln->val, rn->val);
            return Data(val);
        }
    };

    vector<Data> t;
    int n;

    SegTree(vi &a){
        n = a.size();
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vi &a, int v, int lt, int rt){
        if(lt == rt){
            t[v] = Data(a[lt]);
            return;
        }
        int md = lt + (rt - lt)/2;
        build(a, 2*v, lt, md);
        build(a, 2*v+1, md+1, rt);
        t[v] = Data::combine(&t[2*v], &t[2*v + 1]);
    }

    Data query(int v, int lt, int rt, int l, int r){
        if(lt == l && rt == r){
            return t[v];
        }
        int md = lt + (rt - lt)/2;
        Data *lp = nullptr, *rp = nullptr;
        Data ln, rn;
        if(l <= md){
            ln = query(2*v, lt, md, l, min(md,r));
            lp = &ln;
        }
        if(r >= md+1){
            rn = query(2*v+1, md+1, rt, max(md+1,l), r);
            rp = &rn;
        }
        auto ans = Data::combine(lp, rp);
        return ans;
    }

    void updateValue(int v, int lt, int rt, int pos, int value){
        if(lt == rt){
            t[v] = Data(value);
            return;
        }
        int md = lt + (rt - lt)/2;
        if(pos <= md){
            updateValue(2*v, lt, md, pos, value);
        }else{
            updateValue(2*v+1, md+1, rt, pos, value);
        }
        t[v] = Data::combine(&t[2*v], &t[2*v+1]);
    }
};


struct SegTreeLazy{
    /*
        Range Min Queries with range sum query
        - root at vertex 1
    */

    struct Data{
        // val : min value disregarding lz
        ll val;
        ll lz;
        Data(ll val, ll lz = 0) : val(val) , lz(lz) {}
        Data() : Data(0,0) {}

        static Data combine(Data *ln, Data *rn){
            if(ln == nullptr) return *rn;
            if(rn == nullptr) return *ln;
            // merge intervals
            auto val = min(ln->val + ln->lz, rn->val + rn->lz);
            return Data(val);
        }
    };

    vector<Data> t;
    int n;

    SegTreeLazy(vl &a){
        n = a.size();
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void push(int v, int lt, int rt){
        if(lt < rt){ //non-leaf
            t[2*v].lz += t[v].lz;
            t[2*v+1].lz += t[v].lz;
            t[v] = Data::combine(&t[2*v],&t[2*v + 1]);
        }else{
            t[v].val += t[v].lz;
        }
        t[v].lz = 0;
    }

    void build(vl &a, int v, int lt, int rt){
        if(lt == rt){
            t[v] = Data(a[lt]);
            return;
        }
        int md = lt + (rt - lt)/2;
        build(a, 2*v, lt, md);
        build(a, 2*v + 1, md+1, rt);
        t[v] = Data::combine(&t[2*v], &t[2*v + 1]);
    }

    Data query(int v, int lt, int rt, int l, int r){
        push(v, lt, rt);
        if(lt == l && rt == r){
            return t[v];
        }
        int md = lt + (rt - lt)/2;
        Data *lp = nullptr, *rp = nullptr;
        Data ln, rn;
        if(l <= md){
            ln = query(2*v, lt, md, l, min(md,r));
            lp = &ln;
        }
        if(r >= md+1){
            rn = query(2*v+1, md+1, rt, max(md+1,l), r);
            rp = &rn;
        }
        auto ans = Data::combine(lp, rp);
        return ans;
    }

    void updateRange(int v, int lt, int rt, int l, int r, ll add){
        if(l > r) return;
        push(v, lt, rt);
        if(lt == l && rt == r){
            t[v].lz += add;
            return;
        }
        int md = lt + (rt - lt)/2;
        updateRange(2*v, lt, md, l, min(md,r), add);
        updateRange(2*v + 1, md+1, rt, max(md+1,l), r, add);
        t[v] = Data::combine(&t[2*v], &t[2*v+1]);
    }

    ll query(int l, int r = -1){
        if(r == -1) r = n-1;
        return query(1, 0, n-1, l, r).val;
    }

    void updateRange(ll value, int l, int r = -1){
        if(r == -1) r = n-1;
        updateRange(1, 0, n-1, l, r, value);
    }
};

struct SegTreeP{
    /*
        Range Min Queries
    */

    struct Data{
        ll x, add;
        Data(ll x, ll add = 0) : x(x), add(add) {}
        Data() : Data(0) {}

        static Data combine(Data *dl, Data *dr){
            if(dl == nullptr) return *dr;
            if(dr == nullptr) return *dl;
            ll newX = min(dl->x + dl->add , dr->x + dr->add);
            return Data(newX);
        }
    };

    struct Node{
        Node *lp, *rp;
        Data data;
        
        Node() : lp(nullptr) , rp(nullptr) , data(0) {};

        Node(ll value) : Node() {
            data.x = value;
            data.add = 0;
        }
        
        Node(Node *lp, Node *rp) : lp(lp), rp(rp) {
            data = Data::combine(&(lp->data), &(rp->data));
        }

        void push(){
            if(lp != nullptr){
                lp->data.add += data.add;
                rp->data.add += data.add;
                data = Data::combine(&(lp->data), &(rp->data));
            }else{
                data.x += data.add;
            }
            data.add = 0;
        }
    };

    int n;
    Node *root = nullptr;
    
    Node* build(vl &a, int l, int r){
        if (l == r) return new Node(a[l]);
        int k = l + (r - l) / 2;
        Node *ln = build(a, l, k);
        Node *rn = build(a, k+1, r);
        return new Node(ln, rn);
    }

    Data query(Node *v, int lt, int rt, int l, int r)
    {
        v->push();
        if(l == lt && r == rt){
            return v->data;
        }
        int md = lt + (rt - lt) / 2;
        Data ld,rd;
        Data *lp = nullptr, *rp = nullptr;
        if(l <= md){
            ld = query(v->lp, lt, md, l, min(md, r));
            lp = &ld;
        }
        if(r >= md+1){
            rd = query(v->rp, md+1, rt, max(md+1, l), r);
            rp = &rd;
        }
        auto ret = Data::combine(lp, rp);
        return ret;
    }

    void updateRange(Node *v, int lt, int rt, int l, int r, ll value){
        if(l > r) return;
        v->push();
        if(l == lt && r == rt){
            v->data.add += value;
            return;
        }
        int md = lt + (rt - lt) / 2;
        updateRange(v->lp, lt, md, l, min(md, r), value);
        updateRange(v->rp, md+1, rt, max(md+1, l), r, value);
        v->data = Data::combine(&(v->lp->data), &(v->rp->data));
    }

    void clean(Node *v){
        if(v == nullptr) return;
        clean(v->lp);
        clean(v->rp);
        delete v;
    }

    SegTreeP(vl &a){
        this->n = a.size();
        this->root = build(a, 0, n-1);
    }

    ~SegTreeP(){ clean(root); }

    ll query(int l, int r = -1){
        if(r == -1) r = n-1;
        return query(root, 0, n-1, l, r).x;
    }

    void updateRange(ll value, int l, int r = -1){
        if(r == -1) r = n-1;
        updateRange(root, 0, n-1, l, r, value);
    }
  
};

void print_v(vector<ll> v){
    cout << "v: ";
    for_each(v.begin(), v.end(), [](auto x) -> void {cout << x << " ";});
    cout << endl;
}

void test_code_1(){
    int ntest = 10;
    int vsize = 300;
    int nquery = 1000;
    double percent_add = 0.7;
    int maxnum = 10000;

    cout << "Starting tests" << endl;
    
    default_random_engine generator;
    uniform_int_distribution<ll> vdist(0, maxnum);
    uniform_int_distribution<int> idist(0, vsize-1);    
    bernoulli_distribution qdist(percent_add);

    for(int _ = 0; _ < ntest; _++){
        cout << "Test " << _ << endl;
        
        vl v(vsize);
        generate(v.begin(), v.end(), [&]() ->  ll { return vdist(generator);});

        //print_v(v);

        // auto t = SegTreeP(v);
        auto t = SegTreeLazy(v);

        cout << "Starting queries..." << endl;

        for(int __ = 0; __ < nquery; __++){
            int iq = idist(generator);
            int jq = idist(generator);
            if(jq < iq)
                swap(iq,jq);

            if(qdist(generator)){
                //add
                ll add = vdist(generator);
                t.updateRange(add, iq, jq);
                transform(v.begin() + iq, v.begin() + jq + 1, v.begin() + iq, [=](ll x) -> ll {return x + add;});
                cout << "query: add " << add << " in [" << iq << "," << jq << "]" << endl;
                //print_v(v);
            }else{
                //query
                cout << "query: min in [" << iq << "," << jq << "]" << endl;
                auto t_ans = t.query(iq,jq);
                auto ans = *min_element(v.begin()+iq, v.begin()+jq+1);
                cout << "t_ans = " << t_ans << " ans = " << ans << endl;
                
                if(t_ans != ans){
                    cout << "Error :(" << endl;
                    throw exception();
                }else{
                    cout << "Ok" << endl;
                }
            }
        }
    }
    cout << "Passed all the tests :)" << endl;
}

int main(){

    test_code_1();
    
    return 0;
    
}