
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <random>
#include <functional>
#include <tuple>
#include <typeinfo>
#include <assert.h> 
#include <random>

using namespace std;
#define mp make_pair
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = (1 << 30);
typedef long long int li;

class SegTree
{

  private:
    class Node{
        /*
            x: is max interval value
            add: lazy interval add part
        */
        void merge_info(){
            //assert (add == 0);
            if(ln != nullptr){
                auto ldata = ln->x + ln->add;
                auto rdata = rn->x + rn->add;
                x = max(ldata,rdata);
            }
        }

      public:
        Node *ln, *rn;
        li x, add;
        
        Node(li x){
            this->x = x;
            this->add = 0;
            this->ln = this->rn = nullptr;
        }

        Node(Node *ln, Node *rn){
            this->add = 0;
            this->ln = ln;
            this->rn = rn;
            this->merge_info();
        }

        void norm(){
            if(ln != nullptr){
                ln->add += add;
                rn->add += add;
            }else{
                x += add;
            }
            add = 0;
            merge_info();
        }
    };
    
    Node* init(vector<li> &v, int l, int r)
    {
        if (l == r)
            return new Node(v[l]);

        int k = l + (r - l) / 2;
        Node *ln = init(v, l, k);
        Node *rn = init(v, k+1, r);
        return new Node(ln, rn);
    }

    li merge_query(li *lret, li *rret){
        //assert(lret != nullptr || rret != nullptr);

        if(lret == nullptr)
            return *rret;
        if(rret == nullptr)
            return *lret;

        return max(*lret, *rret);
    }

    //query interval [i,j] in current node [l, r]
    li query(Node *curr, int l, int r, int i, int j)
    {
        curr->norm();
        
        if (l >= i && r <= j)
            return curr->x;

        int k = l + (r - l) / 2;

        li *lret = nullptr, *rret = nullptr;

        //[l,k] \inter [i,j]
        if (k >= i && l <= j)
            lret = new li(query(curr->ln, l, k, i, j));
        
        //[k+1,r] \inter [i,j]
        if (k + 1 <= j && r >= i)
            rret = new li(query(curr->rn, k+1,r,i,j));
        
        //merge query
        auto ret = merge_query(lret, rret);
        return ret;
    }

    void add(Node *curr, li k, int i, int j, int l, int r){
        if(j < l || i > r) return;
        
        if(l >= i && r <= j){
            // [l,r] inside [i,j]
            curr->add += k;
        }else{
            int m = l + (r - l) / 2;
            add(curr->ln, k, i, j, l, m);
            add(curr->rn, k, i, j, m+1, r);
        }
        curr->norm();
    }

    int n;
    Node *root = nullptr;

    void clean(Node *v){
        if(v == nullptr) return;
        clean(v->ln);
        clean(v->rn);
        delete v;
    }

  public:

    SegTree(vector<li> &v){
        this->n = v.size();
        this->root = init(v, 0, n-1);
    }

    ~SegTree(){ clean(root); }

    // max element in [i,j]
    li query(int i = 0, int j = -1)
    {
        if(j == -1) j = n-1;
        return query(root, 0, n-1, i, j);
    }

    // adds k in for all values in [i,j]
    void add(li k, int i, int j = -1){
        if(j == -1) j = n-1;
        add(root, k, i, j, 0, n-1);
    }
  
};

void print_v(vector<li> v){
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
    uniform_int_distribution<li> vdist(0, maxnum);
    uniform_int_distribution<int> idist(0, vsize-1);    
    bernoulli_distribution qdist(percent_add);

    for(int _ = 0; _ < ntest; _++){
        cout << "Test " << _ << endl;
        
        vector<li> v(vsize);
        generate(v.begin(), v.end(), [&]() ->  li { return vdist(generator);});

        //print_v(v);

        SegTree t = SegTree(v);

        cout << "Starting queries..." << endl;

        for(int __ = 0; __ < nquery; __++){
            int iq = idist(generator);
            int jq = idist(generator);
            if(jq < iq)
                swap(iq,jq);

            if(qdist(generator)){
                //add
                li add = vdist(generator);
                t.add(add, iq, jq);
                transform(&v[iq], &v[jq+1], &v[iq], [=](li x) -> li {return x + add;});
                cout << "query: add " << add << " in [" << iq << "," << jq << "]" << endl;
                //print_v(v);
            }else{
                //query
                cout << "query: max in [" << iq << "," << jq << "]" << endl;
                auto t_ans = t.query(iq,jq);
                auto ans = *max_element(&v[iq], &v[jq+1]);
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