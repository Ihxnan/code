/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, q;
    cin >> n >> q;
    vl arr(n + 1);
    multiset<int> sma, big;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], big.insert(arr[i]);
    auto modify = [&]() -> void {
        while (big.size() - big.count(*big.begin()) >= n / 2)
        {
            int num = *big.begin(), t = big.count(num);
            while (t--)
                sma.insert(num);
            big.erase(num);
        }
    };
    modify();
    gdb(sma);
    gdb(big);
    for (int i = 0, p, v; i < q; ++i)
    {
        cin >> p >> v;
        gdb(p, v);
        if (arr[p] < *big.begin())
        {
            sma.erase(sma.find(arr[p]));
            arr[p] += v;
            if (arr[p] < *big.begin())
                sma.insert(arr[p]);
            else
                big.insert(arr[p]);
        }
        else
        {
            big.erase(big.find(arr[p]));
            big.insert(arr[p] += v);
        }
        modify();
        gdb(sma);
        gdb(big);
        cout << sma.size() << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
