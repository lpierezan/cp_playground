// =============SegTree Sum ================
class SegTreeSum
{
    public long[] sum;
    public IList<long> v;
    public int n;
    public long sumDefault = 0;

    public SegTreeSum(IList<long> v, int n)
    {
        this.v = v; this.n = n;
        sum = new long[4 * n];
        init(0, 0, n - 1);
    }

    private void init(int node, int ini, int fim)
    {
        if (ini == fim)
        {
            sum[node] = v[ini];
            return;
        }

        int k = ini + (fim - ini) / 2;
        init(2 * node + 1, ini, k);
        init(2 * node + 2, k + 1, fim);

        sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    }


    public long query(int i, int j)
    {
        i = Math.Min(i, j); j = Math.Max(i, j);
        return query(0, 0, n - 1, i, j);
    }

    public long query(int node, int l, int r, int i, int j)
    {
        //contido
        if (l >= i && r <= j)
            return sum[node];

        int k = l + (r - l) / 2;
        long ret = sumDefault;
        bool existeEsq = false;

        //[ini,k] \inter [i,j]
        if (k >= i && l <= j)
        {
            ret = query(2 * node + 1, l, k, i, j);
            existeEsq = true;
        }

        //[k+1,fim] \inter [i,j]
        if (k + 1 <= j && r >= i)
        {
            long dir = query(2 * node + 2, k + 1, r, i, j);

            if (existeEsq)
            {
                ret = ret + dir;
            }
            else
            {
                ret = dir;
            }
        }

        return ret;
    }
}

// =============SegTree Min =================
class SegTreeMin<T>
{
    public int[] vpos;
    public Func<int, int, int> MinPos; //operação cujo domínio são os índices de l

    private int n;
    int posDefault = -1;

    public SegTreeMin(int n, Func<int, int, int> MinPos, int posDefault)
    {
        this.n = n;
        this.posDefault = posDefault;
        vpos = new int[4 * n];
        this.MinPos = MinPos;
        init(0, 0, n - 1);
    }

    private void init(int node, int ini, int fim)
    {
        if (ini == fim)
        {
            vpos[node] = ini;
            return;
        }

        int k = ini + (fim - ini) / 2;
        init(2 * node + 1, ini, k);
        init(2 * node + 2, k + 1, fim);

        vpos[node] = MinPos(vpos[2 * node + 1], vpos[2 * node + 2]);
    }

    public int query(int i, int j)
    {
        i = Math.Min(i, j); j = Math.Max(i, j);
        return query(0, 0, n - 1, i, j);
    }

    private int query(int node, int l, int r, int i, int j)
    {
        //contido
        if (l >= i && r <= j)
            return vpos[node];

        int k = l + (r - l) / 2;
        int ret = posDefault;
        bool existeEsq = false;

        //[ini,k] \inter [i,j]
        if (k >= i && l <= j)
        {
            ret = query(2 * node + 1, l, k, i, j);
            existeEsq = true;
        }

        //[k+1,fim] \inter [i,j]
        if (k + 1 <= j && r >= i)
        {
            int dir = query(2 * node + 2, k + 1, r, i, j);

            if (existeEsq)
            {
                ret = MinPos(ret, dir);
            }
            else
            {
                ret = dir;
            }
        }

        return ret;
    }

}