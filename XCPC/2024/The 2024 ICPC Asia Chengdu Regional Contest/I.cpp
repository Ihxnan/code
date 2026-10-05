#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;

    vvi adj(n + 2);
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= sqrt(i - 1); ++j)
            if ((i - 1) % j == 0)
            {
                if (j != 1)
                    adj[i].push_back(j);
                if (j * j != i - 1)
                    adj[i].push_back((i - 1) / j);
            }

    int cnt = 0;
    vi mp(n + 2);
    vi arr(n + 2);
    vi sta(n + 2);
    vi count(n + 2);
    mp[0] = n - 1;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        if (arr[i] < arr[i - 1])
        {
            ++cnt;
            ++sta[i];
            for (auto &p : adj[i])
            {
                --mp[count[p]];
                ++count[p];
                ++mp[count[p]];
            }
        }
    }

    cout << 1 + mp[cnt] << endl;

    auto work = [&](int idx, int last, int cur) -> void {
        if (last == 1 && cur == 0)
        {
            --cnt;
            for (auto &p : adj[idx])
            {
                --mp[count[p]];
                --count[p];
                ++mp[count[p]];
            }
        }
        else if (last == 0 && cur == 1)
        {
            ++cnt;
            for (auto &p : adj[idx])
            {
                --mp[count[p]];
                ++count[p];
                ++mp[count[p]];
            }
        }
    };

    for (int i = 0, x, y; i < q; ++i)
    {
        cin >> x >> y;

        int p1 = sta[x], p2 = sta[x + 1];
        arr[x] = y;
        sta[x] = arr[x] < arr[x - 1];
        work(x, p1, sta[x]);

        if (x + 1 <= n)
        {
            sta[x + 1] = arr[x + 1] < arr[x];
            work(x + 1, p2, sta[x + 1]);
        }

        cout << 1 + mp[cnt] << endl;
    }
}
