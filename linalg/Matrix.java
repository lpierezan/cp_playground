public class Matrix{
	
	static long[][] multiply(long[][] A, long[][] B, long p){
		int n = A.length;
		int m = B[0].length;
		int c = A[0].length;
		long ans[][] = new long[n][m];

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<c;k++){
					ans[i][j] += (A[i][k] * B[k][j])%p;
					ans[i][j] %= p;
				}
			}
		}

		return ans;
	}

	static long[][] eye(int n){
		long ans[][] = new long[n][n];
		for(int i=0;i<n;i++) ans[i][i] = 1;
		return ans;
    }
    
    static long[][] modPow(long[][] A, long n, long p){
		if(n == 0){
			return eye(A.length);
		}else{
			long[][] ans = modPow(A, n/2, p);
			ans = multiply(ans, ans, p);
			if(n%2 == 1){
				ans = multiply(ans, A, p);
			}
			return ans;
		}
	}
}