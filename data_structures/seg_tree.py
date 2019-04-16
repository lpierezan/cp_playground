# -*- coding: utf-8 -*-
"""
Created on Wed Dec 14 15:34:50 2016

@author: bhq2
"""
#========================================
class node:
    def __init__(self,x):
        self.x = x
        self.add = 0
    
    def norm(self, ln = None, rn = None):
        if ln != None:
            ln.add += self.add
            rn.add += self.add
            self.x = max(ln.x + ln.add , rn.x + rn.add)
        else:
            self.x += self.add            
        self.add = 0
            
class seg_tree:
        
    def __init__(self,v):
        self.n = len(v)
        self.idx = 0
        self.data = [node(None) for i in xrange(4*self.n)]
        self.init(v,0,0,self.n-1)
        
    def init(self,v,idx,li,ri):
        if li == ri:
            #base case
            self.data[idx] = node(v[li])
        else:
            #divide
            mi = (li+ri)/2
            self.init(v,2*idx + 1, li,mi)
            self.init(v,2*idx + 2, mi+1,ri)
            #conquer
            self.norm(idx,li,ri)
            
    def query(self,i,j, idx = 0, li = 0, ri = -1):
        if ri == -1: ri = self.n - 1
        self.norm(idx,li,ri)
        if li >= i and ri <= j:
            #base case
            return self.data[idx].x        
        mi = (li + ri)/2        
        lret = None; rret = None;
        if i <= mi and j >= li: lret = self.query(i,j, 2*idx + 1, li, mi)
        if i <= ri and j >= mi+1: rret = self.query(i,j, 2*idx + 2, mi + 1, ri)        
        ret = self.query_merge(idx,i,j,lret,rret)
        return ret
    
    def norm(self,idx,li,ri):
        if li == ri: self.data[idx].norm()
        else: self.data[idx].norm(self.data[2*idx + 1], self.data[2*idx + 2])
            
    def query_merge(self,idx,i,j,lret,rret):
        ret = None
        if lret == None and rret == None: return None
        if lret != None and rret == None: ret = lret
        if lret == None and rret != None: ret = rret
        if lret != None and rret != None:
            ret = max(lret,rret)
        return ret
        
    def add(self,i,j,add, idx = 0, li = 0, ri = -1):
        if ri == -1: ri = self.n - 1        
        if li >= i and ri <= j:
            #base case
            self.data[idx].add += add
        else:
            mi = (li + ri)/2                
            if i <= mi and j >= li: self.add(i,j,add, 2*idx + 1, li, mi)
            if i <= ri and j >= mi+1: self.add(i,j,add, 2*idx + 2, mi + 1, ri)

        self.norm(idx,li,ri)
#========================================        
""" ========= Test code ==========
"""

import random
        
nteste = 10
vsize = 300
nquery = 1000
percent_add = 0.7
maxnum = 10000

for _ in xrange(nteste):
    vtest = [random.randint(0,maxnum) for i in range(vsize)]
    t = seg_tree(vtest)
    with_error = False
    for __ in xrange(nquery):
        iq = random.randint(0,vsize-1)
        jq = random.randint(iq,vsize-1)
        qt = 'max'
        addq = 0
        if random.random() <= percent_add:
            qt = 'add'
            addq = random.randint(-maxnum,maxnum)
        
        print 'query: ', iq, jq, qt, addq
        if qt == 'max':
            seg_ans = t.query(iq,jq)
            check_ans = max(vtest[iq:jq+1])
            if seg_ans != check_ans:
                print 'Error'
                with_error = True
                break
            else: print "Ok!"
        elif qt == 'add':
            t.add(iq,jq,addq)
            for i in xrange(iq,jq+1): vtest[i] += addq
            
    if with_error: break



            