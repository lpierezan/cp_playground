public class Trie
{
    public int next, root = 1;
    const int num_char = ('z' - 'a' + 1);
    const int min_char = 'a';

    int[][] adj;
    int[] count;

    public Trie(int maxn)
    {
        adj = Init(maxn + 1, num_char, false, 0); count = new int[maxn + 1];
        next = root + 1;
    }

    public void insert(string s)
    {
        int v = root, i = 0;
        while (i < s.Length)
        {
            if (adj[v][s[i] - min_char] == 0)
            {
                v = adj[v][s[i++] - min_char] = next++;
            }
            else
                v = adj[v][s[i++] - min_char];
        }
        count[v]++;
    }
}