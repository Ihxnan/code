#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, x1, y1, x2, y2;
    string str;
    cin >> n >> x1 >> y1 >> x2 >> y2 >> str;
    cout << abs(x1 - x2) + abs(y1 - y2) + n << endl;
    char fx, fy;
    if (x1 <= x2)
        fx = 'L';
    else
        fx = 'R';
    if (y1 <= y2)
        fy = 'D';
    else
        fy = 'U';
    for (auto &p : str)
        if (p == 'L' || p == 'R')
            cout << (p == fx ? 'A' : 'B');
        else
            cout << (p == fy ? 'A' : 'B');
    cout << endl;
}
