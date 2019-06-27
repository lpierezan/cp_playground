class BIT
{
    // 1-indexed 
    public int[] bit;
    public int n;

    public BIT(int n){
        this.n = n;
        bit = new int[n + 1];
    }

    public void update(int i, int val){
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    public int sum(int i){
        int ret = 0;
        for (; i >= 1; i -= i & -i)
            ret += bit[i];
        return ret;
    }

    public static void main(String args[]){
        BIT b = new BIT(4);
        b.update(1, 1);
        b.update(3, 2);
        for(int i=1;i<=4;i++)
            System.out.println("b.sum("+i+")="+b.sum(i));
    }
}