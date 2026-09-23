#include <ihxnan>

int ans;
struct Trie
{
    int tot;
    vvi trie, memo;

    Trie(int n) : tot(0), trie(n + 5, vi(26)), memo(n + 5, vi(26))
    {
    }

    int insert(const string &str, vi &id, int k)
    {
        int cur = 0;
        for (auto &p : str)
        {
            int x = p - 'a';
            if (!trie[cur][x])
                trie[cur][x] = ++tot;
            id.push_back(memo[cur][x]);
            memo[cur][x] = k;
            cur = trie[cur][x];
        }
        return cur;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<string> arr(n);
    for (auto &p : arr)
        cin >> p;

    vvi id(n);
    Trie t(2);
    for (int i = n - 1; i >= 0; --i)
        t.insert(arr[i], id[i], i);
    gdb(id);
}
