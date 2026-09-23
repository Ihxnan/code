#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi cnt(3);
    vvi adj(3);
    ll sum = 0;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], ++cnt[arr[i] % 3], adj[arr[i] % 3].push_back(arr[i]), sum += arr[i];
    sum %= 3;

    if (!cnt[2] && !cnt[1])
        return cout << "NO" << endl, void();

    auto get = [&](int &pre, int &suf) -> int {
        swap(pre, suf);
        if (suf == 0)
            return pre;
        if (suf == 1)
            return (pre + 2) % 3;
        return (pre + 1) % 3;
    };

    for (int pre = 0, suf = sum; pre < 3; ++pre, suf = (suf + 2) % 3)
        if (cnt[pre] && pre != suf)
        {
            vi ans;
            for (auto &p : adj[0])
                ans.push_back(p);

            int a = pre, b = suf;
            int idx[3] = {}, nxt;
            bool flag = false;

            ans.push_back(adj[pre][idx[pre]++]);

            while (true)
            {
                nxt = get(a, b);
                if (nxt == 0)
                    break;
                if (idx[nxt] >= adj[nxt].size())
                    break;
                ans.push_back(adj[nxt][idx[nxt]++]);
            }

            if (idx[1] + idx[2] + 1 == adj[1].size() + adj[2].size())
            {
                if (idx[1] < adj[1].size())
                    ans.push_back(adj[1][idx[1]++]);
                else
                    ans.push_back(adj[2][idx[2]++]);
            }

            if (idx[1] == adj[1].size() && idx[2] == adj[2].size() && ans.back() % 3 == get(a, b))
            {
                cout << "YES" << endl;
                for (auto &p : ans)
                    cout << p << ' ';
                cout << endl;
                return;
            }
        }

    cout << "NO" << endl;
}
