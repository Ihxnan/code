#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;
    int ans = 0;
    map<int, int> hash;
    for (int i = 0, op, x; i < q; ++i)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            ans ^= hash[x];
            ans ^= ++hash[x];
        }
        else
        {
            vi arr;
            for (auto &[k, v] : hash)
            {
                ans ^= v;
                ans ^= --v;
                if (!v)
                    arr.push_back(k);
            }
            for (auto &p : arr)
                hash.erase(p);
        }
        cout << ans << endl;
    }
}
