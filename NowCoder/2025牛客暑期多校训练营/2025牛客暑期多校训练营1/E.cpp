// 1 4 9 16 25 36 49
// 3 5 7 9 11 13
// 8 12 16
// 3 5  7 8 9  11 12 13  15 16 17
// 1     2      3         4
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    ll a, b;
    cin >> a >> b;
    gdb(a, b);
    ll dist = abs(a * a - b * b);
    gdb(dist);
    if (dist == 3)
        cout << 1 << endl;
    else if (dist == 5)
        cout << 2 << endl;
    else
        cout << (dist - 3) / 4 * 3 + (dist + 1) % 4 << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
