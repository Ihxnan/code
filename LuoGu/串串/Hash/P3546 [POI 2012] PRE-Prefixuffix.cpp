#include <ihxnan>
#include <StrHash>

void solve()
{
    int n;
    string str;
    cin >> n >> str;
    int lmid = n / 2 - 1, rmid = (n + 1) / 2;
    StrHash hash(str);
    for (int i = 0; i <= lmid; ++i)
        if (hash.get(0, i) == hash.get(n - 1 - i, n - 1))
        {
            
        }
}
