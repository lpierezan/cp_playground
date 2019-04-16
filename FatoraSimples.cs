// ======================================
public List<Tuple<long, int>> Fatora(long n)
{
    var ret = new List<Tuple<long, int>>();
    if (n <= 1)
    {
        ret.Add(new Tuple<long, int>(n, 0));
        return ret;
    }

    int lim = 10000000; //10^7
    int jump = 1;
    for (long p = 2; p * p <= n && p <= lim; p += jump)
    {
        int exp = 0;
        while (n % p == 0)
        {
            n = n / p;
            exp++;
        }

        if (exp != 0)
            ret.Add(new Tuple<long, int>(p, exp));

        if(p > 2)
            jump = 2;
    }

    if (n != 1)
        ret.Add(new Tuple<long, int>(n, 1));

    return ret;
}
// ======================================