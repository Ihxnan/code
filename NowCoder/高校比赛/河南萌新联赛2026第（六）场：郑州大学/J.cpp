#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll st = 26, sm = 1;
    ll L, R, K, n, t, m;
    cin >> L >> R >> K >> n >> t >> m;

    ll mi = m - sm + abs(t - st);

    n -= mi;

    if (n < 0)
        return cout << "Lie" << endl, void();

    ll sml = min(min(st, t) - L, R - max(st, t)) * 2;
    if (n % K == 0 || n % 2 == 0 || n >= sml || K % 2 && n >= K)
        return cout << "Maybe" << endl, void();

    cout << "Lie" << endl;
}
