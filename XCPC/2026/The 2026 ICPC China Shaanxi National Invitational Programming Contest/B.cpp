#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    lll n, x, y;
    cin >> n >> x >> y;
    string str;
    cin >> str;

    gdb(n, str);

    lll m = (x + y) % n;
    lll c0 = 0, c1 = 0, c2 = 0, pre2 = 0, suf2 = 0;
    for (auto &p : str)
        c0 += p == '0', c1 += p == '1', c2 += p == '2';
    for (int i = 0; i < m; ++i)
        pre2 += str[i] == '2';
    for (int i = m; i < n; ++i)
        suf2 += str[i] == '2';

    gdb(m, x, y);

    if (x + y == 0)
    {
        for (auto &p : str)
            if (p == '2')
                p = '0';
        cout << str << endl;
        return;
    }

    if (x + y < n)
    {
        for (int i = 0; i < m; ++i)
            x -= str[i] == '0', y -= str[i] == '1';
        if (x < 0 || y < 0)
            return cout << -1 << endl, void();
        gdb(x, y);
        for (int i = 0; i < m; ++i)
            if (str[i] == '2')
            {
                if (x > 0)
                    str[i] = '0', --x;
                else
                    str[i] = '1';
            }
        for (auto &p : str)
            if (p == '2')
                p = '0';
        return cout << str << endl, void();
        gdb(2);
    }

    for (int i = 0; i < m; ++i)
        x -= str[i] == '0', y -= str[i] == '1';

    gdb(c0, c1, c2, pre2, suf2);

    lll a1, b1, a2, b2;
    for (a1 = pre2; a1 >= 0; --a1)
    {
        b1 = pre2 - a1;
        gdb(a1, b1, a2, b2);
        gdb((c0 + a1 + a2) * (y - b1), (x - a1) * (c1 + b1 + b2));
        if (((x - a1) * (c1 + b1 + suf2) - (y - b1) * (c0 + a1)) % (x + y - a1 - b1))
            continue;

        a2 = ((x - a1) * (c1 + b1 + suf2) - (y - b1) * (c0 + a1)) / (x + y - a1 - b1);
        b2 = suf2 - a2;

        if (a2 >= 0 && b2 >= 0 && (c0 + a1 + a2) * (y - b1) == (x - a1) * (c1 + b1 + b2))
            break;
    }

    gdb(a1, b1, a2, b2);

    if (a1 < 0)
        return cout << -1 << endl, void();

    for (auto &p : str)
        if (p == '2')
        {
            if (a1 > 0)
                p = '0', --a1;
            else if (b1 > 0)
                p = '1', --b1;
            else if (a2 > 0)
                p = '0', --a2;
            else
                p = '1';
        }

    cout << str << endl;
}
