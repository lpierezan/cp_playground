import numpy as np

def lu_decomp(A):
    n = len(A)
    U = A.copy()
    L = np.eye(n)
    row_idx = list(range(n))

    for col in range(n):
        # find best row
        best_row, best_elem = None, None
        for row in range(col,n):
            row_i = row_idx[row]
            elem = U[row_i][col]
            if best_row is None or abs(elem) > best_elem:
                best_row = row
                best_elem = abs(elem)

        if best_elem == 0:
            #raise(Exception("Not full rank."))
            continue

        # swap rows:  best_row and col
        L[row_idx[col]][col] = 0
        L[row_idx[col]][best_row] = 1
        L[row_idx[best_row]][best_row] = 0
        L[row_idx[best_row]][col] = 1
        row_idx[col], row_idx[best_row] = row_idx[best_row] , row_idx[col]
        best_row_i = row_idx[col]

        # normalize
        for row in range(col+1,n):
            row_i = row_idx[row]
            coef = U[row_i][col] / U[best_row_i][col]
            L[row_i][col] = coef
            U[row_i] = U[row_i] - U[best_row_i] * coef

    return L, U, row_idx

def solve_lu(L_,U_,p,b_):
    L = L_[p]
    U = U_[p]
    b = b_[p]

    n = len(L)
    z = np.zeros(n)
    x = np.zeros(n)
    
    # Lz = b
    # L[i,:i] * sum(z[:i,0] + z[i]) = b[i]
    for i in range(n):
        z[i] = b[i] - (L[i,:i] * z[:i]).sum()

    assert np.allclose(L.dot(z),b)

    # Ux = z
    # U[i,i] * x[i] + sum(U[i,i+1:] * x[i+1:]) = z[i]
    for i in range(n-1,-1,-1):
        acc = (z[i] - (U[i,i+1:] * x[i+1:]).sum())
        if(np.isclose(U[i,i], 0)):
            if(np.isclose(acc,0)):
                # multiple solutions
                x[i] = 0.0
            else:
                # no solution
                raise(Exception('no solution'))
        else:
            x[i] = acc / U[i,i]

    assert np.allclose(U.dot(x),z)

    return x

def test_lu():
    n_teste = 500
    np.random.seed(8)

    while(n_teste > 0):
        n_teste -= 1    
        n = np.random.randint(1,30)
        A = np.random.random((n,n))
        
        if(np.random.random() > 0.5):
            print('Not singular.')
            A[np.random.randint(0,n)] = np.random.uniform(0,100) * A[np.random.randint(0,n)]

        L, U, row_idx = lu_decomp(A)

        L = L[row_idx]
        U = U[row_idx]
        A = A[row_idx]

        assert np.allclose(L.dot(U).ravel(), A.ravel())
    
    print('LU decomposition Ok!')

def test_solve():
    np.random.seed(8)
    n_teste = 10
    while n_teste > 0:
        n_teste -= 1

        n = np.random.randint(1,100)
        A = np.random.random((n,n))
        b = np.random.random(n)

        #A[-1] = A[0]
        #b[-1] = b[0]
        
        ans_correct = np.linalg.solve(A,b)
        
        L,U,p = lu_decomp(A)
        ans = solve_lu(L,U,p,b)

        assert np.allclose(A.dot(ans), b)
        assert np.allclose(ans, ans_correct)
    
    print('Solve with LU Ok!')

if __name__ == "__main__":
    test_lu()
    test_solve()

    
    



