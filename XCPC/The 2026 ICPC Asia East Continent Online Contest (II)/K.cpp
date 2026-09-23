#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    rd0(arr);

    int mex = 0;
    sort(arr.begin(), arr.end());
    for (auto &p : arr)
        mex += p == mex;

    map<int, int> ans;
    for (auto &p : arr)
    {
        int k = mex + p;
        if (!ans.count(k))
        {
            vi sta(n + 2);
            for (auto &p : arr)
            {
                int u = min(p, k - p), v = max(p, k - p);
                if (v > n + 1)
                    v = n + 1;
                if (u < 0 || u > n + 1)
                    u = v;
                sta[u] ? sta[v] = 1 : sta[u] = 1;
            }
            int res = mex;
            while (sta[res])
                ++res;
            ans[k] = res;
        }
    }

    int q;
    int res = 0;
    cin >> q;
    for (int i = 0, t; i < q; ++i)
    {
        cin >> t;
        res ^= ans.count(t) ? ans[t] : mex;
    }
    cout << res << endl;
}
