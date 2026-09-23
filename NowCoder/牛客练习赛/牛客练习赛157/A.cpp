#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int x, y;
    cin >> x >> y;
    if (x < 2 && y < 2)
        return cout << "Bob" << endl, void();
    if (x > y)
        swap(x, y);
    y -= x - 2, x = 2;
    y -= (y - 2) / 6 * 6;

    int flag = 1;
    while (x > 1 || y > 1)
    {
        if (x > y)
            swap(x, y);
        y -= 2, ++x;
        flag ^= 1;
    }

    cout << (flag ? "Bob" : "Alice") << endl;
}
