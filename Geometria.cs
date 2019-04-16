
public struct Ponto
{
    public double x, y;
    public static double eps = 1e-8;

    public Ponto(double x) { this.x = this.y = x; }

    public Ponto(double x, double y) { this.x = x; this.y = y; }

    #region Operadores

    public static bool operator ==(Ponto p1, Ponto p2)
    {
        return Math.Abs(p1.x - p2.x) <= eps && Math.Abs(p1.y - p2.y) <= eps;
    }
    public static bool operator !=(Ponto p1, Ponto p2)
    {
        return !(p1 == p2);
    }

    public static Ponto operator *(double k, Ponto p)
    {
        return new Ponto(p.x * k, p.y * k);
    }
    public static Ponto operator *(Ponto p, double k)
    {
        return k * p;
    }
    public static Ponto operator +(Ponto p1, Ponto p2)
    {
        return new Ponto(p1.x + p2.x, p1.y + p2.y);
    }
    public static Ponto operator -(Ponto p)
    {
        return new Ponto(-p.x, -p.y);
    }
    public static Ponto operator -(Ponto p1, Ponto p2)
    {
        return p1 + (-p2);
    }
    public static bool operator <=(Ponto p1, Ponto p2)
    {
        return p1.x <= (p2.x + eps) && p1.y <= (p2.y + eps);
    }
    public static bool operator >=(Ponto p1, Ponto p2)
    {
        return -p1 <= -p2;
    }

    //produto escalar
    public static double operator *(Ponto p1, Ponto p2)
    {
        return p1.x * p2.x + p1.y * p2.y;
    }

    //produto vetorial
    public static double operator ^(Ponto p1, Ponto p2)
    {
        return p1.x * p2.y - p1.y * p2.x;
    }

    //escalar k | p1 = p2*k
    public static double? operator /(Ponto p1, Ponto p2)
    {
        if (p2 == new Ponto(0) || Math.Abs(p1 ^ p2) > eps) return null;
        if (p2.x != 0) return p1.x / p2.x;
        else return p1.y / p2.y;
    }

    #endregion

    public static bool Colinear(Ponto p1, Ponto p2, Ponto p3)
    {
        return Math.Abs(((p2 - p1) ^ (p3 - p1))) <= eps;
    }

    #region Misc
    public override string ToString()
    {
        return "( " + x + " ; " + y + " )";
    }
    #endregion
}

public class Reta
{
    public double a, b, c; //a*x + b*y + c = 0
    public static double eps = 1e-8;
    public Reta() { }

    public Reta(Ponto p1, Ponto p2)
    {
        Ponto dir = p2 - p1;
        a = -dir.y;
        b = dir.x;
        c = -a * p1.x - b * p1.y;
    }

    public static bool operator ==(Reta r1, Reta r2)
    {
        return Paralela(r1, r2) && (Math.Abs(r1.b * r2.c - r1.c * r2.b) <= eps);
    }
    public static bool operator !=(Reta r1, Reta r2)
    {
        return !(r1 == r2);
    }

    public static bool Paralela(Reta r1, Reta r2)
    {
        return Ponto.Colinear(new Ponto(0), new Ponto(r1.a, r1.b), new Ponto(r2.a, r2.b));
    }

    public bool Contem(Ponto p)
    {
        return Math.Abs(p.x * a + p.y * b + c) <= eps;
    }

    public bool Contem(Segmento seg)
    {
        return this.Contem(seg.p1) && this.Contem(seg.p2);
    }

    public static Ponto? Inter(Reta r1, Reta r2)
    {
        if (r1 == r2) return null; // infinitos pontos
        else if (Paralela(r1, r2)) return null; // nenhum ponto
        Ponto p = new Ponto();

        if (r1.a == 0)
        {
            p.y = -r1.c / r1.b;
            p.x = (-r2.c - r2.b * p.y) / r2.a;
        }
        else
        {
            p.y = (-r2.c + (r1.c * r2.a / r1.a)) / (r2.b - (r1.b * r2.a / r1.a));
            p.x = (-r1.c / r1.a) - (r1.b * p.y / r1.a);
        }

        return p;
    }

}

public class Segmento
{
    public Ponto p1, p2;
    public Reta r;

    public Segmento(Ponto p1, Ponto p2)
    {
        this.p1 = p1; this.p2 = p2;
        this.r = new Reta(p1, p2);
    }

    public bool Contem(Ponto p)
    {
        if (p == p1 || p == p2) return true;
        double? k = (p - p1) / (p2 - p1);
        if (k == null || k < 0 || k > 1) return false;
        return true;
    }

    public static Ponto? Inter(Segmento seg, Reta r)
    {
        Ponto? p = Reta.Inter(r, seg.r);
        if (p == null) return null;

        if (r.Contem(seg.p1)) return seg.p1;
        if (r.Contem(seg.p2)) return seg.p2;

        return seg.Contem((Ponto)p) ? p : null;
    }

}

public class Poligono
{
    public List<Ponto> pontos;

    public Poligono(IEnumerable<Ponto> pontos)
    {
        this.pontos = new List<Ponto>();
        foreach (var p in pontos)
            this.pontos.Add(p);
    }

    public void Clean()
    {
        List<Ponto> npontos = new List<Ponto>();

        for (int i = 0; i < pontos.Count; i++)
        {
            int prox = (i + 1) % pontos.Count;
            int ant = (i + pontos.Count - 1) % pontos.Count;
            if (!Ponto.Colinear(pontos[i], pontos[prox], pontos[ant]))
                npontos.Add(pontos[i]);
        }

        pontos = npontos;
    }

    public double Area()
    {
        double resp = 0;
        for (int i = 2; i < pontos.Count; i++)
        {
            resp += (pontos[i - 1] - pontos[0]) ^ (pontos[i] - pontos[0]);
        }
        return resp;
    }

    public static List<Tuple<Ponto, int>> Inter(Poligono poly, Reta r)
    {
        int i;
        var intersec = new List<Tuple<Ponto, int>>();
        for (i = 0; i < poly.pontos.Count; i++)
        {
            //seg [p_i - p_i+1]
            int prox = (i + 1) % poly.pontos.Count;

            Segmento seg = new Segmento(poly.pontos[i], poly.pontos[prox]);
            if (r.Contem(seg.p1) && r.Contem(seg.p2))
            {
                //intersec.Add(new Tuple<Ponto, bool>(seg.p1, true));
                intersec.Add(new Tuple<Ponto, int>(seg.p2, prox));
            }
            else
            {
                Ponto? p = Segmento.Inter(seg, r);
                if (p != null)
                {
                    bool isExtremo = false;
                    if (p == seg.p1 || p == seg.p2)
                        isExtremo = true;

                    if (!isExtremo || p == seg.p2)
                        intersec.Add(new Tuple<Ponto, int>((Ponto)p, isExtremo ? prox : -1));
                }
            }
        }

        return intersec;
    }
}

