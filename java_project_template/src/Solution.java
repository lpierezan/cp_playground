import java.io.*;
import java.util.*;

public class Solution {

	void run() {
	}
	
	static MyScanner in;
	static PrintWriter out;

	public static void main(String[] args) throws IOException {
		boolean stdStream = true;
		if(stdStream){
			in = new MyScanner();
			out = new PrintWriter(System.out);
		}else{
			String fileName = Solution.class.getSimpleName();
			int n_test = 1;			
			String inputFileName = fileName + String.format(".%02d", n_test) + ".inp";
			String outputFileName = fileName + String.format(".%02d", n_test) + ".out";
			in = new MyScanner(new BufferedReader(new FileReader(inputFileName)));
			out = new PrintWriter(outputFileName);
		}
			
		new Solution().run();

		in.close();
		out.close();
	}

	static class MyScanner {
		BufferedReader br;
		StringTokenizer st;

        MyScanner(){
            this.br = new BufferedReader(new InputStreamReader(System.in));
        }

		MyScanner(BufferedReader br) {
			this.br = br;
        }

        void close() throws IOException {
            br.close();
        }
        
		void findToken() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
		}
		
		String next() {
			findToken();
			return st.nextToken();
		}
		
		int nextInt() {
			return Integer.parseInt(next());
		}
		
		long nextLong() {
			return Long.parseLong(next());
		}
		
		double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}