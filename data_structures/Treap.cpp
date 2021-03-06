#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

class Treap{
    /* Min-Priority heap property
     * Left Subtree => less than
     * Right Subtree => greather or equal
     */
    minstd_rand0 rand_gen;
    
public:
    class node{
    public:
        int v, pr, sz;
        node *l, *r;
        node(int value, int priority) : v(value) , pr(priority){
            sz = 1;
            l = r = nullptr;
        }
        void update(){
            int lsz = l == nullptr ? 0 : l->sz;
            int rsz = r == nullptr ? 0 : r->sz;
            sz = lsz + rsz + 1;
        }
     };
     node *root = nullptr;
     Treap() {}

private:
	void rr(node *&p) {
		//assume p and p->l != NULL
		node *q = p->l;
		p->l = q->r;
		q->r = p;
		p->update(); q->update();
		p = q;
	}

	void lr(node *&p) {
		//assume p and p->r != NULL
		node *q = p->r;
		p->r = q->l;
		q->l = p;
		p->update(); q->update();
		p = q;
	}
	
    void insert(node *&n, int value){
        if(n == nullptr){
            int priority = rand_gen();
            n = new node(value, priority);
            n->update();
            return;
        }
        bool less = value < n->v;
        if(less){ // go left
            insert(n->l, value);
            if(n->l->pr < n->pr)
                rr(n);
        }else{
            insert(n->r, value);
            if(n->r->pr < n->pr)
                lr(n);
        }
        n->update();
    }

    node* find(node *n, int value){
        if(n == nullptr) return nullptr;
        bool less = value < n->v;
        bool equal = n->v == value;
        if(less){
            return find(n->l, value);
        }
        else if(equal){
            return n;
        }else{
            return find(n->r, value);
        }
    }

    bool erase(node *&n, int value){
        if(n == nullptr) return false;
        bool eq = n->v == value;
        bool less = value < n->v;
        bool found = false;
        if(eq){
            erase(n);
            found = true;
        }else if(less){
            found = erase(n->l, value);
        }else{
            found = erase(n->r, value);
        }
        if(n != nullptr) n->update();
        return found;
    }

    void erase(node *&n){
        if(n == nullptr) return;
        if(n->l == nullptr && n->r == nullptr) {delete n; n = nullptr; return; }
        if (n->r == nullptr || (n->l != nullptr && n->l->pr <= n->r->pr)) {
			//left node goes up
			rr(n); erase(n->r);
		}
		else {
			//right node goes up
			lr(n); erase(n->l);
		}
        n->update();
    }

    int kth_elem(node *n, int k){
        int n_less = n->l == nullptr ? 0 : n->l->sz;
        if(k <= n_less) return kth_elem(n->l, k);
        if(k == n_less+1) return n->v;
        return kth_elem(n->r, k - (n_less+1));
    }

    // # nodes s.t node.v < x
    int count_lower(node *n, int x){
        if(n == nullptr) return 0;
        if(n->v >= x) return count_lower(n->l, x);
        int ans = n->l == nullptr ?  0 : n->l->sz;
        ans++;
        return ans + count_lower(n->r, x);
    }

    void clear(node *p) {
		if (p == nullptr) return;
		clear(p->l); clear(p->r);
		delete p; p = nullptr; return;
	}

	void print(node *p, stringstream &ret) {
		if (p == nullptr) return;
		print(p->l, ret);
		ret << "(value = " << std::to_string(p->v) << 
        ", priority = " << p->pr << ")" << endl;
		print(p->r, ret);
	}

public:
    void insert(int value){
        insert(root, value);
    }
    
    bool erase(int value){
        return erase(root, value);
    }
    
    node* find(int value){
        return find(root, value);
    }

    pair<bool,int> kth_elem(int k){
        // 1-indexed
        if(root == nullptr || k <= 0 || k > root->sz)
            return mp(false,0);
        return mp(true, kth_elem(root, k));
    }

    int count_lower(int x){
        return count_lower(root, x);
    }

    ~Treap(){clear(root);}
    void clear() { clear(root);}

    string to_string(){
        stringstream ret;
        print(root, ret);
        return ret.str();
    }
};

int main(){
    // tested on https://www.spoj.com/problems/ORDERSET/
    int nq, i, x;
    char q_ch;
    cin >> nq;
    Treap t;

    for(int iq=0;iq<nq;iq++){
        cin >> q_ch;
        cin >> x;
        if(q_ch == 'I'){
            if(t.find(x) == nullptr)
                t.insert(x);
        }else if (q_ch == 'D')
        {
            t.erase(x);
        }else if (q_ch == 'K')
        {
            auto ans = t.kth_elem(x);
            if(!ans.first)
                cout << "invalid" << endl;
            else
            {
                cout << ans.second << endl;
            }
        }else if (q_ch == 'C')
        {
            cout << t.count_lower(x) << endl;
        }else
        {
            throw invalid_argument("query char: " + q_ch);
        }
    }

    return 0;
}