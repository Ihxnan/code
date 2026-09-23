#include <ihxnan>
#include <KMP>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    str = '^' + str;
    vi nxt = NXT(str);
    cout << n - nxt[n] << endl;
}
