
class UnionFind:
    """
    par[v] = -(# of elements in v´s set), if v is root
    par[v] = j >= 0, if j is parent of v    
    -1 represents empty set
    """
    
    def __init__(self, n):
        self.par = [-1]*n

    def root(self, v):
        if v == -1:
            return v
        r = v
        while self.par[r] >= 0:
            r = self.par[r]        
        
        # r is the root
        while v != r:
            tmp = self.par[v]
            self.par[v] = r
            v = tmp
        
        return r

    def merge(self, u, v):
        u = self.root(u)
        v = self.root(v)

        if u == -1 or v == -1 or (u == v):
            return

        if self.par[u] >= self.par[v]:
            u, v = v, u
        
        # u´s set is bigger
        # link v -> u
        self.par[u] += self.par[v]
        self.par[v] = u

    def size(self, u):
        return 0 if u == -1 else -self.par[self.root(u)]
