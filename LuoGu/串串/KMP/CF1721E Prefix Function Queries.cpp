#include <ihxnan>
#include <KMP>

void solve()
{
    string str;
    cin >> str;
    int n = str.size();
    str = '^' + str;
    vi fail = get_fail(str);
    fail.resize(n + 11);
    vvi tr(n + 11, vi(26));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 26; ++j)
            tr[i][j] = tr[fail[i]][j];
        tr[i][str[i + 1] - 'a'] = i;
    }

    int q;
    cin >> q;
    string s;
    for (int i = 0; i < q; ++i)
    {
        cin >> s;
        str += s;
        for (int j = n + 1, k = fail[n]; j < str.size(); ++j)
        {
            k = tr[k][str[j] - 'a'];
            if (str[j] == str[k + 1])
                ++k;
            fail[j] = k;
            cout << k << ' ';
            for (int l = 0; l < 26; ++l)
                tr[j - 1][l] = tr[fail[j - 1]][l];
            tr[j - 1][str[j] - 'a'] = j - 1;
        }
        cout << endl;
        for (int j = 0; j < s.size(); ++j)
            str.pop_back();
    }
}
