class Trie:
    class node:
        def __init__(self, symb = None, parent = None):
            self.count = 0
            self.parent = parent
            self.symb = symb

            # symbol -> node
            self.child = dict()
        
    def __init__(self):
        self.root = Trie.node()

    def add_word(self, w):
        curr = self.root
        for c in w:
            if c not in curr.child:
                curr.child[c] = Trie.node(c, curr)
            curr = curr.child[c]
        curr.count += 1

    def dfs(self, v = None):
        if(v is None):
            v = self.root

        print('symb:', v.symb);print('count:', v.count)

        for symb, u in v.child.items():
            self.dfs(u)

if __name__ == "__main__":
    
    t = Trie()
    t.add_word('hello!')
    t.add_word('world.')
    t.add_word('hell')

    t.dfs()