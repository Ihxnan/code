/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, q;
    cin >> n >> q;
    string S;
    cin >> S;
    S = '^' + S;
    string T;
    for (int i = 0, a; i < q; ++i)
    {
        ll ans = 0;
        cin >> T >> a;
        T = '^' + T;
        int l = 1;
        for (int r = 1; r < T.size(); ++r)
            if (S[a + r - 1] != T[r])
                l = r + 1;
            else
                ans += r - l + 1;
        cout << ans << endl;
    }
}
/* ╚══════════ /SOLVE ══════════╝ */
