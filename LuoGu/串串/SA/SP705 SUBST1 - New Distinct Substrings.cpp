#include <ihxnan>
#include <SuffixArray>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    SuffixArray SA(str);
    ll ans = str.size() * (str.size() + 1) / 2;
    for (int i = 0; i < str.size() - 1; ++i)
        ans -= SA.lc[i];
    cout << ans << endl;
}
