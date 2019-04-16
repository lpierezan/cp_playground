class Tree
{
    public int n, root;
    public List<int>[] adj;
    public int[] pai, lvl;
    public List<int> ordem;

    public Tree(int n)
    {
        this.n = n;
        adj = new List<int>[n];

        for (int i = 0; i < n; i++)
        {
            adj[i] = new List<int>();
        }
    }

    public void AddEdge(int v, int u)
    {
        adj[v].Add(u);
        adj[u].Add(v);
    }

    public void Root(int v)
    {
        pai = new int[n];
        lvl = new int[n];
        pai[v] = -1;
        lvl[v] = 0;
        this.root = v;

        ordem = new List<int>(n);
        Dfs(v);
    }

    public void Dfs(int v)
    {
        ordem.Add(v);

        foreach (var u in adj[v])
        {
            if (u == pai[v])
            {
                //pai
            }
            else
            {
                //filhos
                pai[u] = v;
                lvl[u] = lvl[v] + 1;
                Dfs(u);
            }
        }
    }

    public int[][] fp; //[i][j] -> [i ... i + 2^j]
    public int logH;

    public void MakeFP()
    {
        int i, j, v;
        logH = (int)Math.Log(n, 2) + 1;

        fp = SS.Init(n, logH + 1, false, 0);

        for (i = 0; i < n; i++)
        {
            v = ordem[i];

            fp[v][0] = pai[v];

            for (j = 1; j <= logH; j++)
            {
                fp[v][j] = -1;

                if (fp[v][j - 1] != -1)
                {
                    fp[v][j] = fp[fp[v][j - 1]][j - 1];
                }
            }
        }
    }

    public int Query_LCA(int u, int v)
    {
        //precisa de MakeFP
        int tmp, log;

        if (u == v)
            return u;

        //u deve estar abaixo em T
        if (lvl[u] < lvl[v])
        {
            tmp = u; u = v; v = tmp;
        }

        //2^log <= lvl[u]
        for (log = 1; 1 << log <= lvl[u]; log++) ;
        log--;

        int pulo = log;
        while (lvl[u] != lvl[v])
        {
            if (lvl[u] - (1 << pulo) >= lvl[v])
                u = fp[u][pulo];
            pulo--;
        }

        if (u == v)
            return u;

        //lvl[u] = lvl[v]
        for (pulo = log; pulo >= 0; pulo--)
        {
            if (fp[u][pulo] != -1 && fp[u][pulo] != fp[v][pulo])
            {
                u = fp[u][pulo]; v = fp[v][pulo];
            }
        }

        return pai[u];
    }

    public override string ToString()
    {
        string ret = "n = " + this.n + "\n";
        for (int i = 0; i < n; i++)
        {
            ret += "adj(" + i + ") = ";
            for (int j = 0; j < adj[i].Count; j++)
                ret += adj[i][j] + " ";

            ret += "\n";
        }
        return ret;
    }

}