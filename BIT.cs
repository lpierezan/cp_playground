public class BIT
{
    public int[] bit;
    public int n;

    public BIT(int n)
    {
        this.n = n;
        bit = new int[n + 1];
    }

    public void update(int i, int val)
    {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    public int sum(int i)
    {
        int ret = 0;
        for (; i >= 1; i -= i & -i)
            ret += bit[i];
        return ret;
    }
}