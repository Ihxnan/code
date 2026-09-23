#include <ihxnan>
#include <SuffixArray>

void solve()
{
    string str;
    cin >> str;
    string ans(str);
    str += str;
    SuffixArray SA(str);
    vi arr(ans.size());
    iota(arr.begin(), arr.end(), 0);
    sort(arr.begin(), arr.end(), [&](int a, int b) { return SA.rk[a] < SA.rk[b]; });
    for (int i = 0; i < arr.size(); ++i)
        ans[i] = str[arr[i] + ans.size() - 1];
    cout << ans << endl;
    gdb(SA.lc);
    gdb(SA.rk);
}
