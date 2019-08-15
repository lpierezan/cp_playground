import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Strings{

    static int[] prefixFunction(char[] p){
        int n = p.length;
        int pi[] = new int[n];
        pi[0] = 0;
        for(int i=1; i<n; i++){
            int j = pi[i-1];
            while(j > 0 && p[i] != p[j]){
                j = pi[j-1];
            }
            if(p[i] == p[j])
                pi[i] = j+1;
        }
        return pi;
    }

    static int[] KMP(char[] p, char[] t){
        // search p in l and returns list of initial hit positions
        List<Integer> hitL = new ArrayList<>();
        int pi[] = prefixFunction(p);
        int j = 0; // position in p to test
        int m = p.length;
        for(int i=0; i+(m-1-j) < t.length; i++){
            while(j > 0 && t[i] != p[j]){
                j = pi[j-1];
            }
            if(t[i] == p[j]){
                j += 1;                
            }
            if(j == p.length){
                hitL.add(i - j + 1);
                j = pi[j-1];
            }
        }
        return hitL.stream().mapToInt(Integer::intValue).toArray();
    }

    static int[][] prefixAutomaton(char[] p){
        //dfa[i][c] = new state when in state = i and receive char = 'a' + c
        //state i represents p[0...i] and last state (#) represents match
        // p += '#'
        
        int n = p.length;
        int nL = 'z' - 'a' + 1;
        int dfa[][] = new int[n+1][nL];
        int pi[] = prefixFunction(p);
        for(int i=0;i<n+1;i++){
            for(int c=0;c<nL;c++){
                if(i > 0 && (i == n || (c+'a' != p[i]))){
                    dfa[i][c] = dfa[pi[i-1]][c];
                }else{
                    if(i < n && (c+'a' == p[i]))
                        dfa[i][c] = i + 1;
                    else
                        dfa[i][c] = 0; // i == 0 and not match
                }
            }
        }
        return dfa;
    }
}