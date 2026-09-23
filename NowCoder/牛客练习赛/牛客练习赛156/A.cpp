#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    string s, t;
    cin >> s >> t;
    for (int i = -10; i <= 10; ++i)
    {
        int x = i;
        int last = abs(x);
        if (s[0] == 'L')
            --x;
        else
            ++x;
        char c = last < abs(x) ? 'F' : 'C';
        if (c != t[0])
            continue;

        last = abs(x);
        if (s[1] == 'L')
            --x;
        else
            ++x;

        c = last < abs(x) ? 'F' : 'C';
        if (c != t[1])
            continue;

        return cout << i << endl, void();
    }
    cout << "T_T" << endl;
}
