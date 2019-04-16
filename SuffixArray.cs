public class SuffixArray
{
    public string s;
    int n, gap;
    int[] sa //sa[i] = i-ésimo menor sufixo
        , pos //pos[s] = posição do sufixo s
        , tmp
        , lcp; //lcp[i] = lcp entre o i-ésimo menor sufixo e o (i+1)-ésimo menor sufixo;

    public SuffixArray(ref string S)
    {
        this.s = S;
        n = s.Length;
        sa = new int[n]; pos = new int[Math.Max(n, 500)]; tmp = new int[n];
        lcp = new int[n];
    }

    int sufCmp(int i, int j)
    {
        if (pos[i] != pos[j])
            return pos[i] < pos[j] ? -1 : 1;
        i += gap;
        j += gap;

        if (i < n && j < n)
            return pos[i] < pos[j] ? -1 : 1;
        else
            return i > j ? -1 : 1;
    }

    void buildSA()
    {
        for (var i = 0; i < n; i++) { sa[i] = i; pos[i] = s[i]; }
        for (gap = 1; ; gap *= 2)
        {
            Array.Sort(sa, sufCmp);

            for (var i = 0; i < n - 1; i++) tmp[i + 1] = tmp[i] + (sufCmp(sa[i], sa[i + 1]) > 0 ? 1 : 0);
            for (var i = 0; i < n; i++) pos[sa[i]] = tmp[i];
            if (tmp[n - 1] == n - 1) break;
        }
    }

    void buildLCP()
    {
        for (int i = 0, k = 0; i < n; ++i) if (pos[i] != n - 1)
            {
                for (int j = sa[pos[i] + 1]; (i + k < n) && (j + k < n) && (s[i + k] == s[j + k]); ++k)

                    lcp[pos[i]] = k;
                if (k != 0) --k;
            }
    }
}