public class SparseTable
{
    public int[][] st; //[i ...i + 2^j - 1]
    public int[] log; //floor[ log(n) ]
    int n, maxp;

    public SparseTable(int[] v)
    {
        n = v.Length;
        log = new int[n + 1];

        log[0] = -1;
        var pow = 1;
        for (var i = 1; i <= n; i++)
        {
            log[i] = log[i - 1];
            if (i == pow)
            {
                ++log[i]; pow *= 2;
            }
        }

        maxp = log[n] + (log[n - 1] != log[n] ? 0 : 1);
        st = Create(n, maxp + 1, false, 0);
        init(v);
    }

    void init(int[] v)
    {
        for (var i = n - 1; i >= 0; i--)
        {
            st[i][0] = v[i];
            for (var j = 1; j <= maxp; j++)
            {
                st[i][j] = st[i][j - 1];
                var pulo = 1 << (j - 1);
                if (i + pulo < n)
                    st[i][j] = Math.Min(st[i][j], st[i + pulo][j - 1]);
            }
        }
    }

    public int Min(int i, int j)
    {
        int k = log[j - i + 1]; var pulo = 1 << k;
        return Math.Min(st[i][k], st[j - pulo + 1][k]);
    }
}