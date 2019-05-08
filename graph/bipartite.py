# import numpy as np
from collections import deque

class bipartite_graph:

    def __init__(self,n,m):
        self.n = n
        self.m = m
        self.g = [list() for i in range(n+m)]
    
    def add_edge(self,v,u):
        if u < v: v,u = u,v
        assert v >= 0 and v < self.n and u >= self.n and u < self.n + self.m
        self.g[v].append(u)
        self.g[u].append(v)

    def _augment(self, v, match):
        if(match[v] >= 0):
            return False
        
        par = [-2]*(n+m) # np.full(n+m, -2, int)
        q = deque()
        par[v] = -1
        q.append(v)
        found = False

        while(len(q) > 0):
            v = q.pop()
            for u in [z for z in self.g[v] if par[z] == -2]:
                par[u] = v
                if(match[u] < 0):
                    found = True
                    break
                elif(par[match[u]] == -2):
                    par[match[u]] = u
                    q.append(match[u])
            if(found):
                break
 
        if(not found):
            return False
        
        # augment match
        while(True):
            match[u] = v
            tmp = match[v]
            match[v] = u
            if(tmp >= 0):
                u = tmp
                v = par[u]
            else:
                break
        return True

    def max_matching(self):
        ans = 0
        match = [-1]*(n+m) # np.full(n+m, -1, int)
        for i in range(self.n):
            if(self._augment(i, match)):
                ans += 1
        return ans


if __name__ == "__main__":
    # https://www.hackerrank.com/challenges/real-estate-broker/problem
    
    n,m = map(int, input().split())

    client = [list(map(int, input().split())) for _ in range(n)]
    house = [list(map(int,input().split())) for _ in range(m)]

    g = bipartite_graph(n,m)
    for i in range(n):
        for j in range(m):
            if(client[i][0] < house[j][0] and client[i][1] >= house[j][1]):
                g.add_edge(i, j+n)

    print(g.max_matching())