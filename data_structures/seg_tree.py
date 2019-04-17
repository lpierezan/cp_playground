# -*- coding: utf-8 -*-

class SegTree:

    class node:
        """
            x: is max interval value
            add: lazy interval add part
        """
        def __init__(self, x = None, ln = None, rn = None):
            self.x = x
            self.add = 0
            self.ln = ln
            self.rn = rn
            self._merge_info()
        
        def _merge_info(self):
            assert self.add == 0
            if self.ln is not None:
                self.x = max(self.ln.x + self.ln.add , self.rn.x + self.rn.add)
            
        def norm(self):
            ln, rn = self.ln, self.rn
            if ln != None:
                # propagete down
                ln.add += self.add
                rn.add += self.add    
            else:
                self.x += self.add

            self.add = 0
            self._merge_info()

    def __init__(self,v):
        self.n = len(v)
        self.idx = 0
        
        self.data = [SegTree.node(None) for i in range(4*self.n)]
        self.init(v,0,0,self.n-1)
        
    def init(self,v,idx,li,ri):
        if li == ri:
            #base case
            self.data[idx] = SegTree.node(v[li])
        else:
            #divide
            mi = (li+ri)//2
            self.init(v,2*idx + 1, li,mi)
            self.init(v,2*idx + 2, mi+1,ri)
            #conquer
            self.data[idx] = SegTree.node(ln = self.data[2*idx + 1], rn = self.data[2*idx + 2])
            
    def query(self,i,j, idx = 0, li = 0, ri = -1):
        if ri == -1: 
            ri = self.n - 1
        
        self.data[idx].norm()        
        if li >= i and ri <= j:
            # [li,ri] in [i,j]
            return self.data[idx].x
        mi = (li + ri)//2        
        lret , rret = None, None
        if i <= mi and j >= li:
            lret = self.query(i,j, 2*idx + 1, li, mi)
        if i <= ri and j >= mi+1: 
            rret = self.query(i,j, 2*idx + 2, mi + 1, ri)
        ret = self.query_merge(idx,i,j,lret,rret)
        return ret
            
    def query_merge(self,idx,i,j,lret,rret):
        ret = None
        if lret == None and rret == None:
            return None
        if lret != None and rret == None:
            ret = lret
        if lret == None and rret != None:
            ret = rret
        if lret != None and rret != None:
            ret = max(lret,rret)
        return ret
        
    def add(self,i,j,add, idx = 0, li = 0, ri = -1):
        if ri == -1:
            ri = self.n - 1
        if li >= i and ri <= j:
            #base case
            self.data[idx].add += add
        else:
            mi = (li + ri)//2                
            if i <= mi and j >= li:
                self.add(i,j,add, 2*idx + 1, li, mi)
            if i <= ri and j >= mi+1:
                self.add(i,j,add, 2*idx + 2, mi + 1, ri)
        self.data[idx].norm()
#========================================        

import random

def test_code_1():

    nteste = 10
    vsize = 300
    nquery = 1000
    percent_add = 0.7
    maxnum = 10000

    for _ in range(nteste):
        vtest = [random.randint(0,maxnum) for i in range(vsize)]
        t = SegTree(vtest)
        for __ in range(nquery):
            iq = random.randint(0,vsize-1)
            jq = random.randint(iq,vsize-1)
            qt = 'max'
            addq = 0
            if random.random() <= percent_add:
                qt = 'add'
                addq = random.randint(-maxnum,maxnum)
            
            print('query: ', iq, jq, qt, addq)
            if qt == 'max':
                seg_ans = t.query(iq,jq)
                check_ans = max(vtest[iq:jq+1])
                if seg_ans != check_ans:
                    print('Error')
                    raise(Exception('Error :('))        
                else:
                    print("Ok!")
            elif qt == 'add':
                t.add(iq,jq,addq)
                for i in range(iq,jq+1): vtest[i] += addq
                
    print('Passed the tests. :)')


if __name__ == '__main__':
    test_code_1()
