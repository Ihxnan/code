#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    string str;
    cin >> str;

    int l = -1, r = -1;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == '?' && l == -1)
            l = i;
        if (str[i] == '?')
            r = i;
    }

    if (l == -1)
        return cout << str << endl, void();

    string mistr = str;

    int ca = 0;
    for (int i = 0; i < l; ++i)
        if (str[i] == ')')
            --ca;
        else if (str[i] == '(')
            ++ca;
    int cb = 0;
    for (int i = n - 1; i > r; --i)
        if (mistr[i] == ')')
            ++cb;
        else if (mistr[i] == '(')
            --cb;

    if (ca > cb)
    {
        ca -= cb;
        for (int i = l; ca; --ca, ++i)
            mistr[i] = ')';
    }
    else if (cb > ca)
    {
        cb -= ca;
        for (int i = r; cb; --cb, --i)
            mistr[i] = '(';
    }
    else
    {
        int tmp = l - 1;
        for (int i = l; ca; --ca, ++i)
            mistr[i] = ')', tmp = i;
        for (int i = r; cb && i > tmp; --cb, --i)
            mistr[i] = '(';
    }

    int idx = -1;
    for (int i = 0; i < n; ++i)
        if (mistr[i] == '?')
        {
            idx = i;
            break;
        }

    if (idx != -1)
        for (int i = idx; i < n; i += 2)
            if (mistr[i] == '?')
                mistr[i] = '(', mistr[i + 1] = ')';

    int cl = 0;
    for (int i = l; i <= r; ++i)
        cl += mistr[i] == '(';

    if (cl == 0 || cl == r - l + 1)
        return cout << mistr << endl, void();

    string mastr = mistr;

    for (int i = l; i <= r; ++i)
        if (cl > 0)
            mastr[i] = '(', --cl;
        else
            mastr[i] = ')';

    auto work = [&](string &str) -> ll {
        ll res = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (str[i] == ')')
                res += cnt--;
            else
                ++cnt;
        return res;
    };

    ll ma = work(mastr);
    gdb(mistr);
    gdb(mastr);
    gdb(work(mistr));
    gdb(work(mastr));

    int fl = l, fr = r;
    while (mastr[fr - 1] == ')')
        --fr;

    ll dif = ma - m;

    while (dif > 0 && fr <= r && fl <= r)
    {
        while (mastr[fl] == mistr[fl])
            ++fl;
        while (fr - fl > dif)
            ++fl;
        dif -= fr - fl;
        swap(mastr[fl++], mastr[fr++]);
    }

    gdb(work(mastr));
    cout << mastr << endl;
}
