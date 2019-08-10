import java.util.function.BiFunction;

class SegTree
{
    static BiFunction<Integer, Integer, Integer> mergeFunc = (i1,i2) -> Math.min(i1,i2);

    class Node {
        Node ln,rn;
        int x;
        Node(int x){
            this.x = x;
            ln = rn = null;
        }
        Node(Node ln, Node rn){
            this.ln = ln;
            this.rn = rn;
            merge();
        }
        void merge(){
            if(ln != null){
                x = mergeFunc.apply(ln.x, rn.x);
            }
        }
    }

    Node root = null;
    int n;

    SegTree(int[] v)
    {
        n = v.length;
        root = init(v, 0, n-1);
    }

    private Node init(int[] v, int l, int r) {
        if(l == r)
            return new Node(v[l]);
        int mid = l + (r-l)/2;
        Node ln = init(v, l,mid);
        Node rn = init(v, mid+1,r);
        return new Node(ln,rn);
    }

    public int query(int i, int j){
        return query(root, 0, n-1, i, j);
    }

    private int query(Node curr, int l, int r, int i, int j){
        // query [i,j] in current node [l,r]
        if(l >= i && r <= j)
            return curr.x;
        int mid = l + (r-l)/2;
        Integer ql = (i <= mid ? query(curr.ln, l, mid, i, j) : null);
        Integer qr = (j >= mid+1 ? query(curr.rn, mid+1, r, i, j) : null);
        if(ql == null) return qr;
        if(qr == null) return ql;
        // merge queries
        int ans = mergeFunc.apply(ql, qr);
        return ans;
    }

    public void update(int pos, int value){
        update(root, 0, n-1, pos, value);
    }

    private void update(Node curr, int l, int r, int pos, int value){
        if(l == r){
            curr.x = value;
            return;
        }
        int mid = l + (r-l)/2;
        if(pos <= mid)
            update(curr.ln, l, mid, pos, value);
        else
            update(curr.rn, mid+1, r, pos, value);

        curr.merge();
    }

    public static void main(String[] args) {
        int[] v = {2,1,5,7,-1};
        SegTree t = new SegTree(v);
        for(int i=0;i<v.length;i++)
            System.out.println(t.query(0, i));
        t.update(2, -10);
        for(int i=0;i<v.length;i++)
            System.out.println(t.query(0, i));
    }
}