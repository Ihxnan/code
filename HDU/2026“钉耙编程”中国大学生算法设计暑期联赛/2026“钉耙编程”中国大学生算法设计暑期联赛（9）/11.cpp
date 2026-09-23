#include <ihxnan>
#include <Comb>

// int init = [] { return cin >> t, 0; }();

Comb comb(mod);
void solve()
{
    gdb(2 * comb.inv(2));
    gdb(2 * comb.inv(3));
}
