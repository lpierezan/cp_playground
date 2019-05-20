#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef long long ll;

class trie{
public:
    class node{
    public:
        char c;
        node* p;
        int count;
        map<char, node*> child;
        node(char c = -1, node* p = nullptr) : c(c) , p(p) {
            count = 0;
        }
        ~node(){
            for(auto u : child){ delete u.second;}
        }
    };
    node *root;

    trie(){ root = new node(); }

    ~trie(){ delete root; }

    void insert(vector<char> word){
        auto curr = root;
        for(char ch : word){
            auto u = curr->child.find(ch);
            if(u == curr->child.end()){
                node *uu = new node(ch, curr);
                curr->child[ch] = uu;
                curr = uu;
            }else{
                curr = (*u).second;
            }
        }
        curr->count += 1;
    }
    void insert(string s){
        insert(vector<char>(s.begin(), s.end()));
    }

    void dfs(node *v = nullptr){
        if(v == nullptr)
            v = root;
        
        cout << "symb = " << v->c << " count = " << v->count << endl;

        for(auto u : v->child){
            node *uu = u.second;
            dfs(uu);
        }
    }
};

int main(){
    trie t;
    t.insert("hello!");
    t.insert("world.");
    t.insert("hell");
    t.dfs();
    return 0;
}