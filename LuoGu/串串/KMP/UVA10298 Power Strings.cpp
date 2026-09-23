#include <ihxnan>

void solve()
{
    string str;
    while (cin >> str, str != ".")
    {
        gdb(str);
        str = '^' + str;
        int n = str.size() - 1;
        vi nxt(str.size());
        for (int i = 2, j = 0; i <= n; ++i)
        {
            while (j && str[i] != str[j + 1])
                j = nxt[j];
            if (str[i] == str[j + 1])
                ++j;
            nxt[i] = j;
        }
        if (n % (n - nxt[n]))
            cout << 1 << endl;
        else
            cout << n / (n - nxt[n]) << endl;
    }
}
