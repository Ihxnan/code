#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int l, r;
    cin >> l >> r;
    if (l & 1)
    {
        if (r & 1)
            cout << "Alice" << endl;
        else
        {
            if (r >= 2 * l)
                cout << "Alice" << endl;
            else
                cout << "Bob" << endl;
        }
    }
    else
    {
        if (r & 1)
            cout << "Bob" << endl;
        else
        {
            if (r >= 2 * (l + 1))
                cout << "Bob" << endl;
            else
                cout << "Alice" << endl;
        }
    }
}
