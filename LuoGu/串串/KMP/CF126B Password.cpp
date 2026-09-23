#include <ihxnan>

void solve()
{
    string str;
    cin >> str;
    int n = str.size();
    str = '^' + str;
    vi nxt(n + 1);
    for (int i = 2, j = 0; i <= n; ++i)
    {
        while (j && str[i] != str[j + 1])
            j = nxt[j];
        if (str[i] == str[j + 1])
            ++j;
        nxt[i] = j;
    }

    int m = nxt[n];
    if (!m)
        return cout << "Just a legend", void();

    int mx = 0;
    for (int i = 2; i < n; ++i)
        mx = max(nxt[i], mx);

    while (nxt[n] > mx)
        n = nxt[n];

    if (nxt[n])
        cout << str.substr(1, nxt[n]) << endl;
    else
        cout << "Just a legend" << endl;
}
