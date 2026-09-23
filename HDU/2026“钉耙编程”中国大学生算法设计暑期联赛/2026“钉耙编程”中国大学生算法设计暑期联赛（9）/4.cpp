#include <ihxnan>
#include <LinearBasis>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, len, q;
    cin >> n >> len >> q;
    vl arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], arr[i] ^= arr[i - 1];

    LinearBasis<ll> line;
    for (int i = len; i <= n; ++i)
        line.insert(arr[i] ^ arr[i - len]);

    ll t;
    for (int i = 0; i < q; ++i)
    {
        cin >> t;
        for (int j = 62; j >= 0; --j)
            if ((t >> j & 1) == 0 && line.basis[j])
                t ^= line.basis[j];
        cout << t << endl;
    }
}
