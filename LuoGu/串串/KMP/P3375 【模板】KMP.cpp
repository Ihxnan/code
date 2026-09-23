#include <ihxnan>

void solve()
{
    string txt, pat;
    cin >> txt >> pat;
    int n = txt.size();
    int m = pat.size();
    txt = '^' + txt;
    pat = '^' + pat;
    vi nxt(m + 1);
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j && pat[i] != pat[j + 1])
            j = nxt[j];
        if (pat[i] == pat[j + 1])
            ++j;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i)
    {
        while (j && txt[i] != pat[j + 1])
            j = nxt[j];
        if (txt[i] == pat[j + 1])
            ++j;
        if (j == m)
            cout << i - m + 1 << endl, j = nxt[j];
    }
    for (int i = 1; i <= m; ++i)
        cout << nxt[i] << ' ';
}
