public class Treap<T>
{
    /* Min-Priority
     * Left Subtree => less than
     * Right Subtree => greather or equal
     */

    public class TreapNode<T>
    {
        public TreapNode(T v, int p)
        {
            Value = v;
            Priority = p;
            Size = 1;
        }

        public T Value { get; set; }
        public int Priority { get; set; }
        public int Size { get; set; }

        public TreapNode<T> Left;
        public TreapNode<T> Right;

        public void Update()
        {
            int lsize = Left != null ? Left.Size : 0;
            int rsize = Right != null ? Right.Size : 0;
            Size = lsize + rsize + 1;
        }
    }

    public Treap () : this(Comparer<T>.Default){}
    public Treap (IComparer<T> comparer)
    {
	    this.comparer = comparer;
	    this.random = new Random();			    
    }

    IComparer<T> comparer;
    TreapNode<T> root;
    Random random;

    void RR(ref TreapNode<T> p)
    {
        var q = p.Left;
        p.Left = q.Right;
        q.Right = p;
        p.Update(); q.Update();                
        p = q;
    }

    void LR(ref TreapNode<T> p)
    {
        var q = p.Right;
        p.Right = q.Left;
        q.Left = p;
        p.Update(); q.Update();
        p = q;
    }

    public void Add (T item)
    {
	    Add(ref root, item);
    }

    void Add (ref TreapNode<T> node, T item)
    {
	    if(node == null){
		    node = new TreapNode<T>(item, random.Next());
            node.Update();
		    Count++;
		    return;
	    }

	    var c = comparer.Compare (item, node.Value);
	    if (c < 0){ // item < node.Value
		    Add(ref node.Left, item);			
		    if(node.Left.Priority < node.Priority){
                RR(ref node);
		    }
	    }
	    else if(c >= 0){ // item >= node.Value
		    Add(ref node.Right, item);
            if (node.Right.Priority < node.Priority)
            {
                LR(ref node);
		    }
	    }
        node.Update();
    }

    public void Clear ()
    {
	    this.root = null;
	    Count = 0;
    }

    public TreapNode<T> GetNode(T key)
    {
	    return GetNode(root, key);
    }
	
    //First node s.t node.Value >= key
    TreapNode<T> GetNode(TreapNode<T> node, T key){
	    if(node == null){
            return null;
	    }
	    int c = comparer.Compare(key, node.Value);
        if (c < 0)
        {
            var srch = GetNode(node.Left, key);
            return srch ?? node;
        }
        if (c == 0)
        {
            return node;
        }
	    //if(c > 0) 
        return GetNode(node.Right, key);
    }

    public bool Contains(T item)
    {
        var node = GetNode(root, item);
        if (node == null || comparer.Compare(item, node.Value) != 0) return false;
        return true;
    }

    public void Remove (T item)
    {
	    Remove(ref root, item);
    }

    void Remove(ref TreapNode<T> node, T item){
	    if(node == null) return;
	    var c = comparer.Compare(item, node.Value);
        if (c == 0) { Remove(ref node);}
        else if (c < 0) Remove(ref node.Left, item);
        else Remove(ref node.Right, item);
        if (node != null) node.Update();
    }

    void Remove(ref TreapNode<T> node)
    {
        if (node == null) return;
        if ((node.Left == null && node.Right == null))
        {
            Count--; 
            node = null;
            return;
        }
        if (node.Right == null || (node.Left != null && node.Left.Priority <= node.Right.Priority))
        {
            RR(ref node);
            Remove(ref node.Right);
        }
        else
        {//R != null && (L == null || L.p > R.P)
            LR(ref node);
            Remove(ref node.Left);
        }
        node.Update();
    }

    public T Kth_Element(int k)
    {
        if (k <= 0 || k > Count) return default(T);
        return Kth_Element(root, k);
    }

    T Kth_Element(TreapNode<T> node, int k)
    {
        int n_less_than = node.Left != null ? node.Left.Size : 0;
        if (k <= n_less_than) return Kth_Element(node.Left, k);
        if (k == n_less_than + 1) return node.Value;
        return Kth_Element(node.Right, n_less_than + 1);
    }

    int CountLessThan(TreapNode<T> node, T t)
    {
        if (node == null) return 0;
        var c = comparer.Compare(t, node.Value);

        if (c <= 0) //t <= node.V
        {
            return CountLessThan(node.Left, t);
        }
        else //t > node.V
            return (node.Left != null ? node.Left.Size : 0) + 1 + CountLessThan(node.Right, t);                
    }

    public int CountLessThan(T t)
    {
        return CountLessThan(root, t);
    }
    
    public int Count { get; private set;}		    
}