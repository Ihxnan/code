#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi fa(n + 1);
    vvi tree(n + 1);
    for (int i = 2; i <= n; ++i)
        cin >> fa[i], tree[fa[i]].push_back(i);

    vi dep(n + 1);
    auto dfs = [&](auto &&self, int r) -> void {
        for (auto &s : tree[r])
            dep[s] = dep[r] + 1, self(self, s);
    };
    dfs(dfs, 1);

    vi vec(n);
    iota(vec.begin(), vec.end(), 1);
    sort(vec.begin(), vec.end(), [&](int x, int y) { return dep[x] > dep[y]; });

    vi arr;
    vb sta(n + 1);
    sta[0] = true;
    for (auto &i : vec)
        if (!sta[i])
        {
            int x = i;
            int cnt = 1;
            sta[x] = true;
            while (!sta[fa[x]])
                x = fa[x], sta[x] = true, ++cnt;
            arr.push_back(cnt);
        }

    sort(arr.begin(), arr.end());

    int cnt = 0;
    int ans = min(int(arr.size()), arr.back());

    while (arr.size())
    {
        ++cnt;
        arr.pop_back();
        ans = min(ans, cnt + (arr.size() ? arr.back() : 0));
    }

    cout << ans << endl;
}
