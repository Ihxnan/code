#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi a(n + 1), b(n + 1);
    rd1(a);
    rd1(b);
    vvi tree(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vi ans(n + 1);
    vi Wa(n + 1);
    vector<multiset<int>> A(n + 1), B(n + 1);

    auto dfs = [&](auto &&self, int f, int r) -> void {
        if (!a[r])
            ++Wa[r];

        if (a[r] && a[r] != b[r])
            A[r].insert(a[r]);
        if (b[r] && b[r] != a[r])
            B[r].insert(b[r]);

        for (auto &s : tree[r])
            if (s != f)
            {
                self(self, r, s);
                if (A[s].size() + B[s].size() > A[r].size() + B[r].size())
                    swap(A[s], A[r]), swap(B[s], B[r]);
                Wa[r] += Wa[s];

                while (A[s].size())
                    if (B[r].count(*A[s].begin()))
                        B[r].erase(B[r].find(*A[s].begin())), A[s].erase(A[s].begin());
                    else
                        A[r].insert(*A[s].begin()), A[s].erase(A[s].begin());
                while (B[s].size())
                    if (A[r].count(*B[s].begin()))
                        A[r].erase(A[r].find(*B[s].begin())), B[s].erase(B[s].begin());
                    else
                        B[r].insert(*B[s].begin()), B[s].erase(B[s].begin());
            }
        if (Wa[r] >= B[r].size())
            ans[r] = 1;
    };

    dfs(dfs, 0, 1);

    for (int i = 1; i <= n; ++i)
        cout << ans[i];
    cout << endl;
}
