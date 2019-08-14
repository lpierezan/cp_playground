import java.util.ArrayList;
import java.util.List;

class Strings{

    static int[] prefixFunction(String p){
        int n = p.length();
        int pi[] = new int[n];
        pi[0] = 0;
        for(int i=1; i<n; i++){
            int j = pi[i-1];
            while(j > 0 && p.charAt(i) != p.charAt(j)){
                j = pi[j-1];
            }
            if(p.charAt(i) == p.charAt(j))
                pi[i] = j+1;
        }
        return pi;
    }

    static int[] KMP(String p, String t){
        // search p in l and returns list of initial hit positions
        List<Integer> hitL = new ArrayList<>();
        int pi[] = prefixFunction(p);
        int j = 0; // position in p to test
        int m = p.length();
        for(int i=0; i+(m-1-j) < t.length(); i++){
            while(j > 0 && t.charAt(i) != p.charAt(j)){
                j = pi[j-1];
            }
            if(t.charAt(i) == p.charAt(j)){
                j += 1;                
            }
            if(j == p.length()){
                hitL.add(i - j + 1);
                j = pi[j-1];
            }
        }
        return hitL.stream().mapToInt(Integer::intValue).toArray();
    }
    
}